#include <game/scenes/MenuScene.hpp>

#include <game/CoreConfig.hpp>
#include <game/Typedefs.hpp>

#include <game/components/Sprite.hpp>
#include <game/components/Transform.hpp>

#include <game/systems/Render.hpp>

#include <game/scenes/GameScene.hpp>

#include <roen/Utils.hpp>
#include <roen/log/Logger.hpp>
#include <roen/manager/GameSceneManager.hpp>

namespace spielda::scenes
{

namespace
{
const std::string menuBackground {"menu_background"};
}

MenuScene::MenuScene(roen::manager::GameSceneManager &gameSceneManager)
    : IScene(gameSceneManager)
    , renderTexture_{LoadRenderTexture(spielda::RENDER_WIDTH, spielda::RENDER_HEIGHT)}
    , camera_{Vector2{0, 0}, Vector2{0, 0}, 0.f, 1.f}
{
    entityManager_.ctx().emplace<spielda::TextureManager>();

    initSystems();
    initEntities();
}

void MenuScene::handleInput()
{

}

void MenuScene::render()
{
    float scale = std::min((float)GetScreenWidth() / spielda::RENDER_WIDTH, (float)GetScreenHeight() / spielda::RENDER_HEIGHT);

    BeginTextureMode(renderTexture_);
    ClearBackground(RAYWHITE);

    systems_.get<system::Render>().update();

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

void MenuScene::update()
{
    //gameSceneManager_.push(std::make_unique<GameScene>(gameSceneManager_));
}

void MenuScene::obscured()
{

}

void MenuScene::revealed()
{
    APP_INFO("Entered MenuScene");
}

void MenuScene::initSystems()
{
    systems_.add<system::Render>(entityManager_, camera_);
}

void MenuScene::initEntities()
{
    initBackground();
}

void MenuScene::initBackground()
{
    entityManager_.ctx().get<spielda::TextureManager>().loadAsset(menuBackground, "assets/textures/menu_background.png");

    constexpr float rotation {0.f};
    constexpr std::uint32_t layer {1};
    constexpr Rectangle backgroundSrcRect {
            .x = 0.f,
            .y = 0.f,
            .width = 1536.f,
            .height = 1024.f
    };

    constexpr Vector2 backgroundPosition {
            .x = 0.f,
            .y = 0.f
    };

    constexpr Vector2 backgroundScale {
            .x = 1.f,
            .y = 1.f
    };

    constexpr Vector2 backgroundSize {
            .x = static_cast<float>(spielda::RENDER_WIDTH),
            .y = static_cast<float>(spielda::RENDER_HEIGHT)
    };

    auto background = entityManager_.create();
    entityManager_.emplace<components::Transform>(background, backgroundPosition, backgroundPosition, backgroundScale, rotation);
    entityManager_.emplace<components::Sprite>(background, backgroundSize, Vector2{0.f, 0.f}, backgroundSrcRect, layer, layer, roen::hashString(menuBackground), true);
}

} // spielda::scenes
