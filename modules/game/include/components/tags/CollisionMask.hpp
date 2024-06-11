#ifndef SPIELDA_GAME_COMPONENTS_TAGS_COLLISIONMASK_HPP
#define SPIELDA_GAME_COMPONENTS_TAGS_COLLISIONMASK_HPP

#include <bitset>

namespace spielda::tags
{

enum MaskLayer : std::uint64_t
{
    PLAYER = 1u << 0,
    ENEMY = 1u << 1,
    DECORATION = 1u << 2
};

/*
 * Entities within the same mask do NOT collide with each other
 */
struct CollisionMask
{
    std::bitset<8> mask;
};

} // spielda::tags

#endif //SPIELDA_GAME_COMPONENTS_TAGS_COLLISIONMASK_HPP
