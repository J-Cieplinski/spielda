#include <game/MapLoader.hpp>

#include <game/Typedefs.hpp>

#include <game/components/BoxCollider.hpp>
#include <game/components/Sprite.hpp>
#include <game/components/Transform.hpp>

#include <roen/log/Logger.hpp>

#include <raymath.h>

#include <regex>

namespace spielda
{

void MapLoader::loadMap(entt::registry& entityManager, const std::string &path, const std::string& assetId)
{
    APP_INFO("Loading map: \"{0}\" with path: \"{1}\"", assetId, path);
    static std::regex reg("(\\.\\.)");

    tson::Tileson tileson;
    auto map = tileson.parse(path);

    auto tileSize = Vector2(map->getTileSize().x, map->getTileSize().y);
    auto rotationOffset = Vector2Scale(tileSize, 0.5f);
    auto scale = Vector2(1.f,1.f);

    auto& textureManager = entityManager.ctx().get<TextureManager>();

    if(map->getStatus() == tson::ParseStatus::OK)
    {
        for(const auto& layer : map->getLayers())
        {
            auto layerOrder = layer.getId();
            auto layerClass = layer.getClassType();

            for (auto& [pos, tile]: layer.getTileData()) {
                auto tileEntity = entityManager.create();

                auto tilePosition = tile->getPosition(pos);
                auto position = Vector2(tilePosition.x, tilePosition.y);

                auto drawingRect = tile->getDrawingRect();

                auto imagePath = std::regex_replace(tile->getTileset()->getFullImagePath().string(), reg, "assets");
                textureManager.loadAsset(assetId, imagePath);

                auto rotation = getTileRotation(tile);

                entityManager.emplace<components::Transform>(tileEntity, Vector2Add(position, rotationOffset), scale, rotation);
                entityManager.emplace<components::Sprite>(tileEntity,
                                                           tileSize,
                                                           Rectangle{static_cast<float>(drawingRect.x),
                                                                     static_cast<float>(drawingRect.y),
                                                                     static_cast<float>(drawingRect.width),
                                                                     static_cast<float>(drawingRect.height)},
                                                           static_cast<std::uint32_t>(layerOrder),
                                                           static_cast<std::uint32_t>(layerOrder),
                                                           roen::hashString(assetId),
                                                           false);

                if(layerClass == "COLLIDABLE" || layerClass == "TRIGGERS")
                {
                    entityManager.emplace<components::BoxCollider>(tileEntity, position, tileSize, false);
                }
            }
        }
    }
}

float MapLoader::getTileRotation(tson::Tile *tile)
{
    auto flippedDiagonally = tile->hasFlipFlags(tson::TileFlipFlags::Diagonally);
    auto flippedHorizontally = tile->hasFlipFlags(tson::TileFlipFlags::Horizontally);
    auto flippedVertically = tile->hasFlipFlags(tson::TileFlipFlags::Vertically);

    if(flippedDiagonally)
    {
        flippedHorizontally = flippedVertically;
        flippedVertically = !tile->hasFlipFlags(tson::TileFlipFlags::Horizontally);
        if(flippedVertically && flippedHorizontally)
        {
            return 270.f;
        }
        else
        {
            return 90.f;
        }
    }
    else if(flippedVertically && flippedHorizontally)
    {
        return 180.f;
    }

    return 0.f;
}

} // spielda
