#include <systems/AIDetect.hpp>

#include <components/AI.hpp>
#include <components/BoxCollider.hpp>
#include <components/CircleCollider.hpp>
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
    const auto colliderView = entityManager_.view<components::CircleCollider>();
    const auto player = entityManager_.view<components::Player>().front();
    const auto playerCollider = colliderView.get<components::CircleCollider>(player);

    auto aiView = entityManager_.view<components::AI>();

    for(auto ai : aiView)
    {
        const auto aiComponent = aiView.get<components::AI>(ai);
        const auto aiCollider = colliderView.get<components::CircleCollider>(ai);

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
