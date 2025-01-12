#include <scenes/MenuScene.hpp>

#include <CoreConfig.hpp>
#include <Typedefs.hpp>
#include <Utilities.hpp>

#include <components/BoxCollider.hpp>
#include <components/Dirty.hpp>
#include <components/GuiElement.hpp>
#include <components/Sprite.hpp>
#include <components/Text.hpp>

#include <components/Transform.hpp>

#include <scenes/GameScene.hpp>
#include <systems/Gui.hpp>
#include <systems/GuiRender.hpp>
#include <systems/Mouse.hpp>
#include <systems/Render.hpp>
#include <systems/TextRender.hpp>

#include <roen/include/Utils.hpp>
#include <roen/include/log/Logger.hpp>
#include <roen/include/manager/GameSceneManager.hpp>

#include <raymath.h>

namespace spielda::scenes
{

namespace
{
const std::string menuBackground {"menu_background"};
}

MenuScene::MenuScene(roen::manager::GameSceneManager &gameSceneManager)
    : IScene{gameSceneManager}
    , renderTexture_{LoadRenderTexture(spielda::RENDER_WIDTH, spielda::RENDER_HEIGHT)}
    , camera_{Vector2{0, 0}, Vector2{0, 0}, 0.f, 1.f}
{
    entityManager_.ctx().emplace<spielda::TextureManager>();
    entityManager_.ctx().emplace<spielda::FontManager>();

    entityManager_.on_construct<components::Sprite>().connect<[&](entt::registry& reg, entt::entity e){
        reg.emplace<components::Dirty>(e);
    }>();

    initAssets();
    initSystems();
    initEntities();
}

MenuScene::~MenuScene()
{
    APP_INFO("Destroyed MenuScene");

    UnloadRenderTexture(renderTexture_);
    auto& fontManager = entityManager_.ctx().get<FontManager>();
    auto& textureManager = entityManager_.ctx().get<TextureManager>();

    fontManager.freeAssets();
    textureManager.freeAssets();
}

void MenuScene::handleInput()
{
}

void MenuScene::render()
{
    float scale = std::min(static_cast<float>(GetScreenWidth()) / RENDER_WIDTH, static_cast<float>(GetScreenHeight()) / RENDER_HEIGHT);

    BeginTextureMode(renderTexture_);
    ClearBackground(RAYWHITE);

    systems_.get<system::Render>().update();
    systems_.get<system::GuiRender>().update();
    systems_.get<system::TextRender>().update();

    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(renderTexture_.texture,
                    Rectangle{ 0.f, 0.f, static_cast<float>(renderTexture_.texture.width), static_cast<float>(-(renderTexture_.texture.height)) },
                    Rectangle{ (GetScreenWidth() - (RENDER_WIDTH * scale)) * 0.5f, (GetScreenHeight() - (RENDER_HEIGHT * scale)) * 0.5f, RENDER_WIDTH * scale, RENDER_HEIGHT * scale },
                    Vector2{ 0, 0 },
                    0.f,
                    WHITE);
    EndDrawing();
}

void MenuScene::update()
{
    systems_.get<system::Mouse>().update();
}

void MenuScene::obscured()
{

}

void MenuScene::revealed()
{
    APP_INFO("Entered MenuScene");
}

void MenuScene::quit()
{
    APP_INFO("Quit MenuScene");
}

void MenuScene::initAssets()
{
    /*
     * Fonts
     */
    auto& fontManager = entityManager_.ctx().get<FontManager>();
    fontManager.loadAsset("immortal", "assets/fonts/IMMORTAL.ttf");

    /*
     * Textures
     */
    auto& textureManager = entityManager_.ctx().get<TextureManager>();
    textureManager.loadAsset(menuBackground, "assets/textures/menu_background.png");
    textureManager.loadAsset("panel_transparent_center", "assets/textures/gui/panel_transparent_center.png");
    textureManager.loadAsset("panel_border", "assets/textures/gui/panel_border.png");
}

void MenuScene::initSystems()
{
    systems_.add<system::Gui>(entityManager_, eventDisptacher_);
    systems_.add<system::GuiRender>(entityManager_);
    systems_.add<system::Mouse>(entityManager_, eventDisptacher_);
    systems_.add<system::Render>(entityManager_, camera_);
    systems_.add<system::TextRender>(entityManager_);
}

void MenuScene::initEntities()
{
    initBackground();
    initButtons();
}

void MenuScene::initBackground()
{
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

    constexpr Vector2 backgroundSize {
        .x = static_cast<float>(RENDER_WIDTH),
        .y = static_cast<float>(RENDER_HEIGHT)
    };

    constexpr Vector2 backgroundScale {
        .x = backgroundSize.x / backgroundSrcRect.width,
        .y = backgroundSize.y / backgroundSrcRect.height,
    };


    auto background = entityManager_.create();
    entityManager_.emplace<components::Transform>(background, backgroundPosition, backgroundPosition, backgroundScale, rotation);
    entityManager_.emplace<components::Sprite>(background, backgroundSize, Vector2{0.f, 0.f}, backgroundSrcRect, layer, layer, roen::hashString(menuBackground), true);
}

void MenuScene::initButtons()
{
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

    auto callback = std::make_unique<SwitchSceneFunctor<GameScene>>(gameSceneManager_); //TODO: change this to lua function 
    auto button = entityManager_.create();
    entityManager_.emplace<components::Transform>(button, buttonPosition, buttonPosition, buttonScale, rotation);
    entityManager_.emplace<components::BoxCollider>(button, colliderPosition, colliderPosition, buttonSize, CollisionType::NONE);
    entityManager_.emplace<components::GuiElement>(button, nPatchInfo, buttonSize, buttonOrigin, roen::hashString("panel_border"), roen::hashString("panel_transparent_center"), false, std::move(callback));
    entityManager_.emplace<components::Text>(button, "Start", roen::hashString("immortal"), 22.f, WHITE);
}

} // spielda::scenes
