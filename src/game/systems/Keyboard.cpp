#include <game/systems/Keyboard.hpp>

#include <game/components/BoxCollider.hpp>
#include <game/components/Health.hpp>
#include <game/components/Player.hpp>
#include <game/components/Sprite.hpp>
#include <game/components/RigidBody.hpp>
#include <game/components/Transform.hpp>
#include <game/components/Weapon.hpp>

#include <game/events/DebugSwitch.hpp>
#include <game/events/Attack.hpp>

#include <game/log/formatters/entity.hpp>

#include <roen/Utils.hpp>
#include <roen/log/Logger.hpp>

#include <entt/entt.hpp>
#include <raylib.h>

namespace spielda::system
{

Keyboard::Keyboard(entt::registry &entityManager, entt::dispatcher& eventDispatcher)
    : ISystem(entityManager)
    , eventDispatcher_(eventDispatcher)
{
}

void Keyboard::update()
{

    if(IsKeyReleased(KEY_D))
    {
        auto debugEnt = entityManager_.create();
        constexpr Rectangle srcRect {
                .x = 0.f,
                .y = 128.f,
                .width = 16.f,
                .height = 16.f
        };
        constexpr std::uint32_t layer = 5;
        constexpr std::uint32_t layerOrder = 1;
        constexpr Vector2 position {
                .x = 81,
                .y = 128
        };

        entityManager_.emplace<components::Sprite>(debugEnt, Vector2{16, 16}, Vector2{0, 0}, srcRect, layer, layerOrder, roen::hashString("dungeon"), false);
        entityManager_.emplace<components::BoxCollider>(debugEnt, position, position, Vector2{14, 12}, false);
        entityManager_.emplace<components::Transform>(debugEnt, position, position, Vector2{1, 1}, 0.f);
        entityManager_.emplace<components::RigidBody>(debugEnt, Vector2{0, 0});
        entityManager_.emplace<components::Health>(debugEnt, 100u, 100u);

        APP_INFO("Added debug entity {0}", debugEnt);
    }

    checkDebugInput();

    checkPlayerInput();
}

void Keyboard::checkDebugInput()
{
    if(IsKeyReleased(KEY_F1))
    {
        eventDispatcher_.trigger(events::DebugSwitch{.switchRender = true});
    }
    if(IsKeyReleased(KEY_F2))
    {
        eventDispatcher_.trigger(events::DebugSwitch{.switchAppLogging = true});
    }
    if(IsKeyReleased(KEY_F3))
    {
        eventDispatcher_.trigger(events::DebugSwitch{.switchSdkLogging = true});
    }
    if(IsKeyReleased(KEY_SPACE))
    {
        auto playerEntity = entityManager_.view<components::Weapon>();
        eventDispatcher_.trigger(events::Attack{.attacker = playerEntity.front()});
    }
}

void Keyboard::checkPlayerInput()
{
    auto playerEntity = entityManager_.view<components::Player>().front();
    auto& playerRigidBody = entityManager_.get<components::RigidBody>(playerEntity);

    playerRigidBody.velocity.x = 0;
    playerRigidBody.velocity.y = 0;

    if(IsKeyDown(KEY_UP))
    {
        playerRigidBody.velocity.y = -30;
    }
    else if(IsKeyDown(KEY_DOWN))
    {
        playerRigidBody.velocity.y = 30;
    }
    else if(IsKeyDown(KEY_LEFT))
    {
        playerRigidBody.velocity.x = -30;
    }
    else if(IsKeyDown(KEY_RIGHT))
    {
        playerRigidBody.velocity.x = 30;
    }
}

} // spielda::system