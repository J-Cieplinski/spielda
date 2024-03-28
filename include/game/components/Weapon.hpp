#ifndef SPIELDA_GAME_COMPONENTS_WEAPON_HPP
#define SPIELDA_GAME_COMPONENTS_WEAPON_HPP

#include <raylib.h>
#include <entt/entity/entity.hpp>

namespace spielda::components
{

struct Weapon
{
    Vector2 relativePosition;
    entt::entity parentEntity;
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_WEAPON_HPP
