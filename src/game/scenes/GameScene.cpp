#include <game/scenes/GameScene.hpp>

#include <game/CoreConfig.hpp>
#include <game/MapLoader.hpp>
#include <game/Typedefs.hpp>

#include <game/components/BoxCollider.hpp>
#include <game/components/Sprite.hpp>
#include <game/components/Transform.hpp>

#include <game/systems/CollisionRender.hpp>
#include <game/systems/Render.hpp>

#include <roen/Utils.hpp>
#include <roen/log/Logger.hpp>
#include <roen/manager/GameSceneManager.hpp>

namespace spielda::scenes
{

GameScene::GameScene(roen::manager::GameSceneManager& gameSceneManager)
    : IScene(gameSceneManager)
    , camera_{Vector2{0, 0}, Vector2{0, 0}, 0.f, 1.f}
{
    renderTexture_ = LoadRenderTexture(spielda::RENDER_WIDTH, spielda::RENDER_HEIGHT);
    systems_.add<system::Render>(entityManager_, camera_);
    systems_.add<system::CollisionRender>(entityManager_, camera_);
    entityManager_.ctx().emplace<TextureManager>();
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

}

void GameScene::obscured()
{

}

void GameScene::revealed()
{
    APP_INFO("Entered GameScene");

    MapLoader::loadMap(entityManager_, "assets/maps/dungeon.tmj", "dungeon");

    entityManager_.sort<components::Sprite>([](const components::Sprite& lhs, const components::Sprite& rhs) {
        return lhs.layer < rhs.layer;});
}

} // spielda::scenes