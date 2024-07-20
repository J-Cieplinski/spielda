#include <systems/AIDetect.hpp>

#include <components/AI.hpp>
#include <components/Player.hpp>
#include <components/BoxCollider.hpp>

#include <events/AIDetectedEnemy.hpp>

#include <Utils.hpp>

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

void AIDetect::update()
{
    const auto player = entityManager_.view<components::Player>().front();
    const auto playerCollider = entityManager_.get<components::BoxCollider>(player);

    const Vector2 playerCenter {
        .x = playerCollider.position.x + playerCollider.size.x / 2.f,
        .y = playerCollider.position.y + playerCollider.size.y / 2.f
    };

    auto aiView = entityManager_.view<components::AI>();

    for(auto ai : aiView)
    {
        const auto aiComponent = entityManager_.get<components::AI>(ai);
        const auto aiCollider = entityManager_.get<components::BoxCollider>(ai);
        const auto aiEntityCenter = Vector2Add(aiCollider.position, Vector2Scale(aiCollider.size, 0.5f));

        if(CheckCollisionCircleRec(aiEntityCenter, aiComponent.detectRadius, playerCollider))
        {
            eventDispatcher_.trigger(events::AIDetectedEnemy {
                .detectedEntityPosition = playerCenter,
                .aiEntity = ai
            });
        }
        else
        {
            entityManager_.get<components::AI>(ai).state = components::AIState::IDLE;
        }
    }
}

} // spielda::system
