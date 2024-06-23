#include <loader/BaseMapLoader.hpp>

#include <log/Logger.hpp>

#include <regex>

namespace roen::loader
{

BaseMapLoader::BaseMapLoader(entt::registry& entityManager)
    : entityManager_{entityManager}
    , mapSize_{0.f, 0.f}
{
}

void BaseMapLoader::loadMap(const std::string& path, const std::string& assetId)
{
    SDK_INFO("Loading map: {0} with path: {1}", assetId, path);

    tson::Tileson tileson;
    auto map = tileson.parse(path);
    mapSize_ = {map->getSize().x, map->getSize().y};

    auto tileSize = map->getTileSize();

    auto& textureManager = getTextureManager();

    if(map->getStatus() == tson::ParseStatus::OK)
    {
        for(auto& layer : map->getLayers())
        {
            auto layerOrderProp = layer.getProp(LayerProperties::RENDER_ORDER);

            if(!layerOrderProp)
            {
                SDK_CRITICAL("Lack of layerOrderProp in layer: {0} of map: {1}", layer.getName(), path);
                return;
            }

            auto layerOrder = std::any_cast<int>(layerOrderProp->getValue());

            auto layerClass = layer.getClassType();

            for (auto& [pos, tile]: layer.getTileData()) {

                auto tilePosition = tile->getPosition(pos);

                auto drawingRect = tile->getDrawingRect();

                auto imagePath = std::regex_replace(tile->getTileset()->getFullImagePath().string(), reg, "assets");
                textureManager.loadAsset(assetId, imagePath);

                auto rotation = getTileRotation(tile);

                addComponents(tilePosition, tileSize, rotation, drawingRect, layerOrder, layerClass, assetId);
            }
        }
    }
}

float BaseMapLoader::getTileRotation(tson::Tile *tile)
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

const std::pair<float, float>& BaseMapLoader::getMapSize() const
{
    return mapSize_;
}

} // roen::loader
