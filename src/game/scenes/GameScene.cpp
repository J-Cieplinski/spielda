#include <game/scenes/GameScene.hpp>

#include <game/CoreConfig.hpp>
#include <game/MapLoader.hpp>
#include <game/Typedefs.hpp>

#include <game/components/BoxCollider.hpp>
#include <game/components/Dirty.hpp>
#include <game/components/Player.hpp>
#include <game/components/Sprite.hpp>
#include <game/components/Transform.hpp>

#include <game/systems/CollisionRender.hpp>
#include <game/systems/Movement.hpp>
#include <game/systems/Keyboard.hpp>
#include <game/systems/Render.hpp>

#include <entt/entt.hpp>

#include <roen/Utils.hpp>
#include <roen/log/Logger.hpp>
#include <roen/manager/GameSceneManager.hpp>

namespace spielda::scenes
{

GameScene::GameScene(roen::manager::GameSceneManager& gameSceneManager)
    : IScene(gameSceneManager)
    , deltaTime_{0}
    , timeLastFrame_{GetTime()}
    , renderTexture_{LoadRenderTexture(spielda::RENDER_WIDTH, spielda::RENDER_HEIGHT)}
    , camera_{Vector2{0, 0}, Vector2{0, 0}, 0.f, 1.f}
{
    initSystems();

    entityManager_.ctx().emplace<TextureManager>();

    entityManager_.on_construct<components::Sprite>().connect<[&](entt::registry& reg, entt::entity e){
        reg.emplace<components::Dirty>(e);
    }>();
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
    systems_.get<system::CollisionRender>().update();

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
}

void GameScene::obscured()
{

}

void GameScene::revealed()
{
    APP_INFO("Entered GameScene");

    auto mapLoader = MapLoader(entityManager_);
    mapLoader.loadMap(entityManager_, "assets/maps/dungeon.tmj", "dungeon");
    auto mapSize = mapLoader.getMapSize();

    loadHero();
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
            .y = 24
    };

    entityManager_.emplace<components::Sprite>(hero, Vector2{16, 16}, Vector2{0, 0}, srcRect, layer, layerOrder, roen::hashString("dungeon"), false);
    entityManager_.emplace<components::Transform>(hero, position, Vector2{1, 1}, 0.f);
    entityManager_.emplace<components::BoxCollider>(hero, position, Vector2{16, 16}, false);
    entityManager_.emplace<components::Player>(hero);
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
    systems_.add<system::CollisionRender>(entityManager_, camera_);
    systems_.add<system::Keyboard>(entityManager_);
    systems_.add<system::Movement>(entityManager_);
    systems_.add<system::Render>(entityManager_, camera_);
}

} // spielda::scenes