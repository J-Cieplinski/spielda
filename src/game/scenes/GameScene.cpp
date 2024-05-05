#include <game/scenes/GameScene.hpp>

#include <game/CoreConfig.hpp>
#include <game/MapLoader.hpp>
#include <game/Typedefs.hpp>

#include <game/components/BoxCollider.hpp>
#include <game/components/Dirty.hpp>
#include <game/components/Player.hpp>
#include <game/components/RigidBody.hpp>
#include <game/components/Sprite.hpp>
#include <game/components/Transform.hpp>
#include <game/components/Weapon.hpp>

#include <game/systems/Collision.hpp>
#include <game/systems/CollisionRender.hpp>
#include <game/systems/WallBoundaries.hpp>
#include <game/systems/Movement.hpp>
#include <game/systems/Keyboard.hpp>
#include <game/systems/Render.hpp>
#include <game/systems/SpriteDirection.hpp>
#include <game/systems/WeaponFollow.hpp>

#include <roen/Utils.hpp>
#include <roen/log/Logger.hpp>
#include <roen/manager/GameSceneManager.hpp>

#include <entt/entt.hpp>
#include <raymath.h>

namespace spielda::scenes
{

GameScene::GameScene(roen::manager::GameSceneManager& gameSceneManager)
    : IScene(gameSceneManager)
    , deltaTime_{0}
    , timeLastFrame_{GetTime()}
    , renderTexture_{LoadRenderTexture(spielda::RENDER_WIDTH, spielda::RENDER_HEIGHT)}
    , camera_{Vector2{0, 0}, Vector2{0, 0}, 0.f, 1.f}
    , debugRender_{true}
{
    initSystems();

    entityManager_.ctx().emplace<TextureManager>();

    entityManager_.on_construct<components::Sprite>().connect<[&](entt::registry& reg, entt::entity e){
        reg.emplace<components::Dirty>(e);
    }>();

    eventDisptacher_.sink<events::DebugSwitch>().connect<&GameScene::switchDebug>(this);
}

void GameScene::handleInput()
{

}

void GameScene::render()
{
    float scale = std::min((float)GetScreenWidth() / spielda::RENDER_WIDTH, (float)GetScreenHeight() / spielda::RENDER_HEIGHT);

    BeginTextureMode(renderTexture_);
    ClearBackground(RAYWHITE);

    systems_.get<system::Render>().update();
    if(debugRender_)
    {
        systems_.get<system::CollisionRender>().update();
    }

    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(renderTexture_.texture,
                   Rectangle{ 0.f, 0.f, static_cast<float>(renderTexture_.texture.width), static_cast<float>(-(renderTexture_.texture.height)) },
                   Rectangle{ (GetScreenWidth() - (spielda::RENDER_WIDTH * scale)) * 0.5f, (GetScreenHeight() - (spielda::RENDER_HEIGHT * scale)) * 0.5f, static_cast<float>(spielda::RENDER_WIDTH * scale), static_cast<float>(spielda::RENDER_HEIGHT * scale) },
                   Vector2{ 0, 0 },
                   0.f,
                   WHITE);
    EndDrawing();
}

void GameScene::update()
{
    updateDeltaTime();
    systems_.get<system::Keyboard>().update();
    systems_.get<system::Movement>().update(deltaTime_);
    systems_.get<system::SpriteDirection>().update();
    systems_.get<system::WeaponFollow>().update();
    systems_.get<system::Collision>().update();
}

void GameScene::obscured()
{

}

void GameScene::revealed()
{
    APP_INFO("Entered GameScene");

    auto mapLoader = MapLoader(entityManager_);
    mapLoader.loadMap("assets/maps/dungeon.tmj", "dungeon");
    auto mapSize = mapLoader.getMapSize();

    loadHero();
}

void GameScene::quit()
{

}

void GameScene::loadHero()
{
    auto hero = entityManager_.create();
    constexpr Rectangle srcRect {
            .x = 0.f,
            .y = 112.f,
            .width = 16.f,
            .height = 16.f
    };
    constexpr std::uint32_t layer = 5;
    constexpr std::uint32_t layerOrder = 1;
    constexpr Vector2 position {
            .x = 24,
            .y = 32
    };
    constexpr Vector2 colliderPosition {
            .x = 24,
            .y = 36
    };

    entityManager_.emplace<components::Sprite>(hero, Vector2{16, 16}, Vector2{0, 0}, srcRect, layer, layerOrder, roen::hashString("dungeon"), false);
    entityManager_.emplace<components::Transform>(hero, position, position, Vector2{1, 1}, 0.f);
    entityManager_.emplace<components::BoxCollider>(hero, colliderPosition, colliderPosition, Vector2{14, 12}, false);
    entityManager_.emplace<components::RigidBody>(hero, Vector2{0, 0});
    entityManager_.emplace<components::Player>(hero);

    constexpr Vector2 weaponPosition {
            .x = 7,
            .y = -3
    };
    constexpr Rectangle weaponSrcRect {
            .x = 128.f,
            .y = 128.f,
            .width = 16.f,
            .height = 16.f
    };

    auto weapon = entityManager_.create();

    entityManager_.emplace<components::Weapon>(weapon, weaponPosition, hero);
    entityManager_.emplace<components::BoxCollider>(weapon, weaponPosition, weaponPosition, Vector2{14, 12}, false);
    entityManager_.emplace<components::Transform>(weapon, Vector2Add(position, weaponPosition), Vector2Add(position, weaponPosition), Vector2{1, 1}, 0.f);
    entityManager_.emplace<components::Sprite>(weapon, Vector2{16, 16}, Vector2{0, 0}, weaponSrcRect, layer + 1, layerOrder, roen::hashString("dungeon"), false);
}

void GameScene::updateDeltaTime()
{
    deltaTime_ = 0;

    auto currentTime = GetTime();
    auto updateDrawTime = currentTime - timeLastFrame_;
    auto targetFrametime = 1.f / 144;
    auto timeToWait = targetFrametime - updateDrawTime;
    if (timeToWait > 0)
    {
        WaitTime(timeToWait);
        currentTime = GetTime();
    }

    deltaTime_ = currentTime - timeLastFrame_;
    timeLastFrame_ = currentTime;
}

void GameScene::initSystems()
{
    systems_.add<system::Collision>(entityManager_, eventDisptacher_);
    systems_.add<system::CollisionRender>(entityManager_, camera_);
    systems_.add<system::WallBoundaries>(entityManager_, eventDisptacher_);
    systems_.add<system::Keyboard>(entityManager_, eventDisptacher_);
    systems_.add<system::Movement>(entityManager_);
    systems_.add<system::Render>(entityManager_, camera_);
    systems_.add<system::SpriteDirection>(entityManager_);
    systems_.add<system::WeaponFollow>(entityManager_);
}

void GameScene::switchDebug(const events::DebugSwitch& event)
{
    debugRender_ = event.switchRender ? !debugRender_ : debugRender_;

    if(event.switchAppLogging)
    {
        roen::log::Logger::getAppLogger()->level() == spdlog::level::off ? roen::log::Logger::setAppLogLevel(spdlog::level::trace)
                                                                            : roen::log::Logger::setAppLogLevel(spdlog::level::off);
    }

    if(event.switchSdkLogging)
    {
        roen::log::Logger::getSdkLogger()->level() == spdlog::level::off ? roen::log::Logger::setSdkLogLevel(spdlog::level::trace)
                                                                            : roen::log::Logger::setSdkLogLevel(spdlog::level::off);
    }
}

} // spielda::scenes