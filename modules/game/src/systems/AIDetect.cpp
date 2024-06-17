#include <systems/AIDetect.hpp>

#include <components/AI.hpp>
#include <components/Player.hpp>
#include <components/BoxCollider.hpp>

#include <events/AIDetectedEnemy.hpp>

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

    const Rectangle collisionBox = {
        .x = playerCollider.position.x,
        .y = playerCollider.position.y,
        .width = playerCollider.size.x,
        .height = playerCollider.size.y
    };

    const Vector2 playerMiddlePos {
        .x = playerCollider.position.x + collisionBox.width / 2.f,
        .y = playerCollider.position.y + collisionBox.height / 2.f
    };

    auto aiView = entityManager_.view<components::AI>();

    for(auto ai : aiView)
    {
        const auto aiComponent = entityManager_.get<components::AI>(ai);
        const auto aiCollider = entityManager_.get<components::BoxCollider>(ai);
        const auto aiMiddle = Vector2Add(aiCollider.position, Vector2Scale(aiCollider.size, 0.5f));

        if(CheckCollisionCircleRec(aiMiddle, aiComponent.detectRadius, collisionBox))
        {
            eventDispatcher_.trigger(events::AIDetectedEnemy {
                .detectedEntityPosition = playerMiddlePos,
                .aiEntity = ai
            });
        }
    }
}

} // spielda::system
