#ifndef SPIELDA_GAME_COMPONENTS_WIELDEDWEAPON_HPP
#define SPIELDA_GAME_COMPONENTS_WIELDEDWEAPON_HPP

#include <raylib.h>
#include <entt/entity/entity.hpp>

namespace spielda::components
{

struct WieldedWeapon
{
    entt::entity weaponEntity;
    Vector2 colliderAttachOffset;
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_WIELDEDWEAPON_HPP
