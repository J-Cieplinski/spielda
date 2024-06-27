#include <loader/BaseMapLoader.hpp>

#include <log/Logger.hpp>

#include <regex>

namespace roen::loader
{

BaseMapLoader::BaseMapLoader(entt::registry& entityManager)
    : entityManager_{entityManager}
    , mapSize_{0u, 0u}
{
}

void BaseMapLoader::loadMap(const std::string& path, const std::string& assetId)
{
    SDK_INFO("Loading map: {0} with path: {1}", assetId, path);

    tson::Tileson tileson;
    auto map = tileson.parse(path);
    mapSize_ = {map->getSize().x, map->getSize().y};
    std::vector<MapTile> mappedTiles{};

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

                if(layerClass == LayerTypes::BACKGROUND)
                {
                    if(auto tileMoveCost = tile->getProp(TileProperties::MOVEMENT_COST))
                    {
                        mappedTiles.emplace_back(std::any_cast<int>(tileMoveCost->getValue()),
                                                 tson::Vector2i {static_cast<int>(tilePosition.x), static_cast<int>(tilePosition.y)});
                    }
                }

                auto drawingRect = tile->getDrawingRect();

                auto imagePath = std::regex_replace(tile->getTileset()->getFullImagePath().string(), reg, "assets");
                textureManager.loadAsset(assetId, imagePath);

                auto rotation = getTileRotation(tile);

                addComponents(tilePosition, tileSize, rotation, drawingRect, layerOrder, layerClass, assetId);
            }
        }

        createPathfindingGraph(mappedTiles, tileSize);
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

const std::pair<std::uint32_t, std::uint32_t>& BaseMapLoader::getMapSize() const
{
    return mapSize_;
}

void BaseMapLoader::createPathfindingGraph(const std::vector<MapTile>& tiles, tson::Vector2i tileSize)
{
    //                                                          NW                              W                                  SW
    std::vector<tson::Vector2i> DIRECTIONS_WITH_DIAGONAL = {{-tileSize.x, -tileSize.y}, {-tileSize.x, 0}, {-tileSize.x, tileSize.y},
    //                                                      N                       S
                                            {0, -tileSize.y}, {0, tileSize.y},
    //                                                      NE                                  E                                   SE
                                            {tileSize.x, -tileSize.y}, {tileSize.x, 0}, {tileSize.x, tileSize.y}};

    std::vector<tson::Vector2i> DIRECTIONS = {
    /*W*/   {-tileSize.x, 0},
    /*N*/   {0, -tileSize.y},
    /*S*/   {0, tileSize.y},
    /*E*/   {tileSize.x, 0} };

    auto findTile = [&tiles](tson::Vector2i position) {
        return std::find_if(tiles.begin(), tiles.end(), [&position](const MapTile& checkedTile) -> bool {
            return checkedTile.position == position;
        });
    };

    auto tileExist = [&](auto checkedTile) {
        return checkedTile != tiles.end();
    };

    for(const auto& tile : tiles)
    {
        std::vector<data_structure::MapNode> edges {};
        for(const auto& direction : DIRECTIONS)
        {
            tson::Vector2i neigbourPos {tile.position.x + direction.x, tile.position.y + direction.y};
            auto mapTile = findTile(neigbourPos);
            if(tileExist(mapTile))
            {
                edges.push_back({{neigbourPos.x, neigbourPos.y}, {tileSize.x, tileSize.y}, static_cast<uint32_t>(mapTile->cost)});
            }
        }

        pathfindingGraph_.addNode({{tile.position.x, tile.position.y}, {tileSize.x, tileSize.y}, static_cast<uint32_t>(tile.cost)},
                                  edges);
    }
}

const data_structure::Graph<data_structure::MapNode>& BaseMapLoader::getGraph() const
{
    return pathfindingGraph_;
}

} // roen::loader
