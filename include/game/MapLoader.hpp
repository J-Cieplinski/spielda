#ifndef SPIELDA_MAPLOADER_HPP
#define SPIELDA_MAPLOADER_HPP

#include <entt/entity/registry.hpp>

#include <tileson/tileson.hpp>

namespace spielda
{

class MapLoader
{
public:
    static void loadMap(entt::registry& entityManager, const std::string &path, const std::string& assetId);
private:
    static float getTileRotation(tson::Tile* tile);
};

} // spielda


#endif //SPIELDA_MAPLOADER_HPP