#include <systems/AIDetect.hpp>

#include <components/AI.hpp>
#include <components/Collider.hpp>
#include <components/Player.hpp>

#include <events/AIDetectedEnemy.hpp>

#include <Utilities.hpp>

#include <roen/include/log/Logger.hpp>

#include <entt/entity/registry.hpp>

#include <raylib.h>
#include <raymath.h>

namespace spielda::system
{

AIDetect::AIDetect(entt::registry& entityManager, entt::dispatcher& dispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{dispatcher}
{

}

void AIDetect::update() const
{
    //TODO: temporary move to variant, need to be changed
    const auto colliderView = entityManager_.view<components::Collider>();
    const auto player = entityManager_.view<components::Player>().front();
    const auto playerCollider = std::get<components::CircleCollider>(colliderView.get<components::Collider>(player));

    auto aiView = entityManager_.view<components::AI>();

    for(auto ai : aiView)
    {
        const auto aiComponent = aiView.get<components::AI>(ai);
        const auto aiCollider = std::get<components::CircleCollider>(colliderView.get<components::Collider>(ai));

        if(CheckCollisionCircles(aiCollider.position, aiComponent.detectRadius, playerCollider.position, playerCollider.radius))
        {
            eventDispatcher_.trigger(events::AIDetectedEnemy {
                .detectedEntityPosition = playerCollider.position,
                .aiEntity = ai
            });
        }
        else
        {
            aiView.get<components::AI>(ai).state = components::AIState::IDLE;
        }
    }
}

} // spielda::system
