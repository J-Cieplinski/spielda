#include <game/scenes/MenuScene.hpp>

#include <game/CoreConfig.hpp>
#include <game/Typedefs.hpp>

#include <game/components/BoxCollider.hpp>
#include <game/components/Dirty.hpp>
#include <game/components/GuiElement.hpp>
#include <game/components/Sprite.hpp>
#include <game/components/Transform.hpp>

#include <game/scenes/GameScene.hpp>

#include <game/systems/CollisionRender.hpp>
#include <game/systems/GuiRender.hpp>
#include <game/systems/Render.hpp>

#include <roen/Utils.hpp>
#include <roen/log/Logger.hpp>
#include <roen/manager/GameSceneManager.hpp>

#include <raymath.h>

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

    entityManager_.on_construct<components::Sprite>().connect<[&](entt::registry& reg, entt::entity e){
        reg.emplace<components::Dirty>(e);
    }>();

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
    systems_.get<system::GuiRender>().update();
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
    systems_.add<system::CollisionRender>(entityManager_, camera_);
    systems_.add<system::GuiRender>(entityManager_);
    systems_.add<system::Render>(entityManager_, camera_);
}

void MenuScene::initEntities()
{
    initBackground();
    initButtons();
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

void MenuScene::initButtons()
{
    entityManager_.ctx().get<spielda::TextureManager>().loadAsset("panel_transparent_border", "assets/textures/gui/panel_transparent_border.png");
    entityManager_.ctx().get<spielda::TextureManager>().loadAsset("panel_border", "assets/textures/gui/panel_border.png");

    constexpr float rotation {0.f};
    constexpr Rectangle backgroundSrcRect {
        .x = 0.f,
        .y = 0.f,
        .width = 48.f,
        .height = 48.f
    };

    constexpr Vector2 buttonPosition {
        .x = 320.f,
        .y = 240.f
    };

    constexpr Vector2 buttonScale {
        .x = 1.f,
        .y = 1.f
    };

    constexpr Vector2 buttonSize {
        .x = 144.f,
        .y = 24.f
    };

    constexpr Vector2 colliderPosition {
            .x = buttonPosition.x - buttonSize.x / 2,
            .y = buttonPosition.y - buttonSize.y / 2
    };

    const Vector2 buttonOrigin = Vector2Scale(buttonSize, 0.5f);

    constexpr NPatchInfo nPatchInfo {
        .source = backgroundSrcRect,
        .left = 12,
        .top = 12,
        .right = 12,
        .bottom = 12,
        .layout = NPATCH_NINE_PATCH
    };

    auto button = entityManager_.create();
    entityManager_.emplace<components::Transform>(button, buttonPosition, buttonPosition, buttonScale, rotation);
    entityManager_.emplace<components::BoxCollider>(button, colliderPosition, colliderPosition, buttonSize, false);
    entityManager_.emplace<components::GuiElement>(button, nPatchInfo, buttonSize, buttonOrigin, roen::hashString("panel_border"), roen::hashString("panel_transparent_border"), false);
}

} // spielda::scenes
