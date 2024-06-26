#ifndef SPIELDA_BASEMAPLOADER_HPP
#define SPIELDA_BASEMAPLOADER_HPP

#include <data_structure/Graph.hpp>
#include <data_structure/MapNode.hpp>
#include <manager/AssetManager.hpp>

#include <entt/entity/registry.hpp>

#include <tileson/tileson.hpp>

#include <regex>
#include <utility>

namespace roen::loader
{

struct LayerTypes
{
    inline static std::string BACKGROUND {"BACKGROUND"};
    inline static std::string TRIGGERS {"TRIGGERS"};
    inline static std::string COLLIDABLE {"COLLIDABLE"};
};

struct LayerProperties
{
    inline static std::string RENDER_ORDER {"renderOrder"};
};

struct TileProperties
{
    inline static std::string MOVEMENT_COST {"movementCost"};
};

class BaseMapLoader
{
public:
    explicit BaseMapLoader(entt::registry& entityManager);

    void loadMap(const std::string &path, const std::string& assetId);
    [[nodiscard]] const std::pair<std::uint32_t, std::uint32_t>& getMapSize() const;
    const data_structure::Graph<data_structure::MapNode>& getGraph() const;
protected:
    struct MapTile
    {
        std::int32_t cost {-1};
        tson::Vector2i position;
    };

    static float getTileRotation(tson::Tile* tile);
    virtual void addComponents(tson::Vector2f tilePosition, tson::Vector2i tileSize, float rotation, tson::Rect drawingRect, int layerOrder,
                               const std::string& layerClass, const std::string& assetId) = 0;
    virtual manager::IAssetManager& getTextureManager() = 0;

    std::pair<std::uint32_t, std::uint32_t> mapSize_;
    entt::registry& entityManager_;
    inline static std::regex reg{"(\\.\\.)"};
    data_structure::Graph<data_structure::MapNode> pathfindingGraph_;
private:
    void createPathfindingGraph(const std::vector<MapTile>& tiles, tson::Vector2i tileSize);
};

} // roen::loader


#endif //SPIELDA_BASEMAPLOADER_HPP