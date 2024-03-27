#include <game/systems/WallBoundaries.hpp>

#include <game/components/BoxCollider.hpp>
#include <game/components/RigidBody.hpp>
#include <game/components/Transform.hpp>

#include <roen/log/Logger.hpp>

#include <entt/entt.hpp>

namespace spielda::system
{

WallBoundaries::WallBoundaries(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem(entityManager)
{
    eventDispatcher.sink<events::Collision>().connect<&WallBoundaries::onCollision>(this);
}

void WallBoundaries::onCollision(const events::Collision& event)
{
    auto firstMovable = entityManager_.try_get<components::RigidBody>(event.firstCollider);
    auto secondMovable = entityManager_.try_get<components::RigidBody>(event.secondCollider);
    if(firstMovable && secondMovable)
    {
        return;
    }

    if(firstMovable)
    {
        rewindEntity(event.firstCollider);
        return;
    }
    else
    {
        rewindEntity(event.secondCollider);
        return;
    }
}

void WallBoundaries::rewindEntity(entt::entity entity)
{
    auto& collider = entityManager_.get<components::BoxCollider>(entity);
    auto& transform = entityManager_.get<components::Transform>(entity);

    collider.position = collider.previousPosition;
    transform.position = transform.previousPosition;
}

} // spielda::system