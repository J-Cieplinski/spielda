#include <game/scenes/GameScene.hpp>

#include <game/CoreConfig.hpp>
#include <game/Typedefs.hpp>
#include <game/components/Transform.hpp>
#include <game/components/Sprite.hpp>
#include <game/systems/Render.hpp>

#include <roen/log/Logger.hpp>
#include <roen/manager/GameSceneManager.hpp>
#include <roen/Utils.hpp>

#include <tileson/tileson.hpp>
#include <raymath.h>

#include <regex>

namespace spielda::scenes
{

GameScene::GameScene(roen::manager::GameSceneManager& gameSceneManager)
    : IScene(gameSceneManager)
    , camera_{Vector2{0, 0}, Vector2{0, 0}, 0.f, 1.f}
{
    renderTexture_ = LoadRenderTexture(spielda::RENDER_WIDTH, spielda::RENDER_HEIGHT);
    systems_.add<system::Render>(entityManager_, camera_);
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

    tson::Tileson tileson;
    auto map = tileson.parse("assets/maps/dungeon.tmj");

    auto tileSize = map->getTileSize();

    if(map->getStatus() == tson::ParseStatus::OK)
    {
        auto backgroundLayer = map->getLayer("Tile Layer 1");
        auto layerOrder = backgroundLayer->getId();
        for(auto& [pos, tile] : backgroundLayer->getTileObjects())
        {
            auto tileset = tile.getTile()->getTileset();
            auto tileEntity = entityManager_.create();
            auto tilePosition = tile.getPosition();
            auto drawingRect = tile.getDrawingRect();
            auto imagePath = tileset->getFullImagePath();

            std::regex reg("(\\.\\.)");
            auto correctImagePath = std::regex_replace(imagePath.string(), reg, "assets");
            auto& manager = entityManager_.ctx().get<TextureManager>();
            manager.loadAsset("dungeon", correctImagePath);
            auto tileFlip = tile.getTile()->hasFlipFlags(tson::TileFlipFlags::Diagonally);
            float rotation = tileFlip ? 90.f : 0.f;
            auto positionVector = Vector2(tilePosition.x + tileSize.x / 2.f, tilePosition.y + tileSize.y / 2);


            entityManager_.emplace<components::Transform>(tileEntity, positionVector, Vector2{1.f, 1.f}, rotation);
            entityManager_.emplace<components::Sprite>(tileEntity,
                                                       Vector2{static_cast<float>(tileSize.x), static_cast<float>(tileSize.y)},
                                                       Rectangle{static_cast<float>(drawingRect.x), static_cast<float>(drawingRect.y), static_cast<float>(drawingRect.width), static_cast<float>(drawingRect.height)},
                                                       static_cast<std::uint32_t>(layerOrder),
                                                       static_cast<std::uint32_t>(layerOrder),
                                                       roen::hashString("dungeon"),
                                                       false);
        }
    }
}

} // spielda::scenes