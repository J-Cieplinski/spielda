#include <systems/WallBoundaries.hpp>

#include <components/BoxCollider.hpp>
#include <components/RigidBody.hpp>
#include <components/Transform.hpp>

#include <roen/include/log/Logger.hpp>

#include <entt/entt.hpp>

namespace spielda::system
{

WallBoundaries::WallBoundaries(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem{entityManager}
{
    eventDispatcher.sink<events::Collision>().connect<&WallBoundaries::onCollision>(this);
}

void WallBoundaries::onCollision(const events::Collision& event)
{
    auto view = entityManager_.view<components::RigidBody, components::BoxCollider, components::Transform>();
    auto firstMovable = view.contains(event.firstCollider);
    auto secondMovable = view.contains(event.secondCollider);
    if(firstMovable && secondMovable)
    {
        return;
    }

    if(firstMovable)
    {
        rewindEntity(event.firstCollider, view);
    }
    else
    {
        rewindEntity(event.secondCollider, view);
    }
}

void WallBoundaries::rewindEntity(entt::entity entity, auto& view)
{
    auto& collider = view.template get<components::BoxCollider>(entity);
    auto& transform = view.template get<components::Transform>(entity);

    collider.position = collider.previousPosition;
    transform.position = transform.previousPosition;
}

} // spielda::system