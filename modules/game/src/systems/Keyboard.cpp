#include <ranges>
#include <systems/Keyboard.hpp>

#include <components/AI.hpp>
#include <components/CharacterSheet.hpp>
#include <components/CircleCollider.hpp>
#include <components/Health.hpp>
#include <components/Player.hpp>
#include <components/RigidBody.hpp>
#include <components/Sprite.hpp>
#include <components/Transform.hpp>
#include <components/WieldedWeapon.hpp>
#include <components/tags/CollisionMask.hpp>


#include <events/DebugSwitch.hpp>
#include <events/Attack.hpp>

#include <roen/include/log/formatters/entity.hpp>

#include <roen/include/Utils.hpp>
#include <roen/include/log/Logger.hpp>

#include <entt/entt.hpp>
#include <raylib.h>
#include <raymath.h>
#include <oneapi/tbb/detail/_task.h>

namespace spielda::system
{

Keyboard::Keyboard(entt::registry &entityManager, entt::dispatcher& eventDispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{eventDispatcher}
{
}

void Keyboard::update()
{
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
    if(IsKeyReleased(KEY_D))
    {
        spawnDebugEntity();
    }
    if(IsKeyReleased(KEY_LEFT_SHIFT))
    {
        for(auto i : std::ranges::iota_view{1, 100})
        {
            spawnDebugEntity();
        }
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
        playerRigidBody.lastVelocity.y = -1;
        playerRigidBody.lastVelocity.x = 0;
    }
    else if(IsKeyDown(KEY_DOWN))
    {
        playerRigidBody.velocity.y = 30;
        playerRigidBody.lastVelocity.y = 1;
        playerRigidBody.lastVelocity.x = 0;
    }
    else if(IsKeyDown(KEY_LEFT))
    {
        playerRigidBody.velocity.x = -30;
        playerRigidBody.lastVelocity.x = -1;
        playerRigidBody.lastVelocity.y = 0;
    }
    else if(IsKeyDown(KEY_RIGHT))
    {
        playerRigidBody.velocity.x = 30;
        playerRigidBody.lastVelocity.x = 1;
        playerRigidBody.lastVelocity.y = 0;
    }
    if(IsKeyReleased(KEY_SPACE))
    {
        if(const auto weapon = entityManager_.try_get<components::WieldedWeapon>(playerEntity))
        {
            eventDispatcher_.trigger(events::Attack{.attacker = weapon->weaponEntity});
        }
        else
        {
            eventDispatcher_.trigger(events::Attack{.attacker = playerEntity});
        }
    }
}

void Keyboard::spawnDebugEntity()
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
    const Vector2 colliderPosition = Vector2Add(position, Vector2Scale({16, 16}, 0.5f));

    entityManager_.emplace<components::AI>(debugEnt, 40.f);
    entityManager_.emplace<components::CharacterSheet>(debugEnt, 10, 10);
    entityManager_.emplace<components::CircleCollider>(debugEnt, colliderPosition, colliderPosition, 6, CollisionType::NONE);
    entityManager_.emplace<components::Health>(debugEnt, 100u, 100u);
    entityManager_.emplace<components::RigidBody>(debugEnt, Vector2{0, 0}, Vector2{1, 0});
    entityManager_.emplace<components::Sprite>(debugEnt, Vector2{16, 16}, Vector2{0, 0}, srcRect, layer, layerOrder, roen::hashString("dungeon"), false);
    entityManager_.emplace<components::Transform>(debugEnt, position, position, Vector2{1, 1}, 0.f);
    entityManager_.emplace<tags::CollisionMask>(debugEnt, tags::MaskLayer::ENEMY | tags::MaskLayer::MOVING);

    APP_INFO("Added debug entity {0}", debugEnt);
}

} // spielda::system