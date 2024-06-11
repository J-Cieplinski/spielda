#ifndef SPIELDA_BASEMAPLOADER_HPP
#define SPIELDA_BASEMAPLOADER_HPP

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

class BaseMapLoader
{
public:
    explicit BaseMapLoader(entt::registry& entityManager);

    void loadMap(const std::string &path, const std::string& assetId);
    [[nodiscard]] const std::pair<float, float>& getMapSize() const;
protected:
    static float getTileRotation(tson::Tile* tile);
    virtual void addComponents(tson::Vector2f tilePosition, tson::Vector2i tileSize, float rotation, tson::Rect drawingRect, int layerOrder,
                               const std::string& layerClass, const std::string& assetId) = 0;
    virtual manager::IAssetManager& getTextureManager() = 0;

    std::pair<float, float> mapSize_;
    entt::registry& entityManager_;
    inline static std::regex reg{"(\\.\\.)"};
};

} // roen::loader


#endif //SPIELDA_BASEMAPLOADER_HPP