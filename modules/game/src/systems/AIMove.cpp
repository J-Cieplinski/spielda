#include <systems/AIMove.hpp>

#include <components/BoxCollider.hpp>
#include <components/RigidBody.hpp>

#include <entt/entity/registry.hpp>

#include <raymath.h>

namespace spielda::system
{

AIMove::AIMove(entt::registry& entityManager, entt::dispatcher& dispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{dispatcher}
{
    eventDispatcher_.sink<events::AIDetectedEnemy>().connect<&AIMove::onDetect>(this);
}

void AIMove::onDetect(events::AIDetectedEnemy event)
{
    const auto aiCollider = entityManager_.get<components::BoxCollider>(event.aiEntity).position;
    auto& aiVelocity = entityManager_.get<components::RigidBody>(event.aiEntity).velocity;

    auto moveVector = Vector2Normalize(Vector2Subtract(event.detectedEntityPosition, aiCollider));

    constexpr std::uint16_t velocity {30};
    aiVelocity = Vector2Scale(moveVector, velocity);
}

} // spielda::system