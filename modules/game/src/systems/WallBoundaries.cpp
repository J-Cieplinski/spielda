#include <systems/WallBoundaries.hpp>

#include <components/CircleCollider.hpp>
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
    if(event.collisionType != CollisionType::WALL)
    {
        return;
    }

    auto view = entityManager_.view<components::RigidBody, components::CircleCollider, components::Transform>();
    const auto firstMovable = view.contains(event.firstCollider);
    const auto secondMovable = view.contains(event.secondCollider);
    if(firstMovable && secondMovable)
    {
        return;
    }

    firstMovable ? rewindEntity(event.firstCollider, view) : rewindEntity(event.secondCollider, view);
}

void WallBoundaries::rewindEntity(entt::entity entity, auto& view)
{
    auto& collider = view.template get<components::CircleCollider>(entity);
    auto& transform = view.template get<components::Transform>(entity);

    collider.position = collider.previousPosition;
    transform.position = transform.previousPosition;
}

} // spielda::system