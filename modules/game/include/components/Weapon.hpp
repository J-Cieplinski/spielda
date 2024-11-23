#ifndef SPIELDA_GAME_COMPONENTS_WEAPON_HPP
#define SPIELDA_GAME_COMPONENTS_WEAPON_HPP

#include <raymath.h>
#include <entt/entity/entity.hpp>

#include <set>

namespace spielda::components
{

struct Weapon
{
    entt::entity wielder;
    Vector2 originPosition;
    std::int32_t damage;
    bool attacking {false};
    std::set<entt::entity> damagedEntities {};
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_WEAPON_HPP
