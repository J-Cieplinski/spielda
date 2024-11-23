#ifndef SPIELDA_MAPLOADER_HPP
#define SPIELDA_MAPLOADER_HPP

#include <loader/BaseMapLoader.hpp>

namespace spielda
{

class MapLoader : public roen::loader::BaseMapLoader
{
public:
    explicit MapLoader(entt::registry& entityManager);
private:
    void addComponents(Vector2 tilePosition, Vector2 tileSize, float rotation, tson::Rect drawingRect, int layerOrder,
                       const std::string& layerClass, const std::string& assetId) override;
    roen::manager::IAssetManager& getTextureManager() override;
};

} // spielda


#endif //SPIELDA_MAPLOADER_HPP