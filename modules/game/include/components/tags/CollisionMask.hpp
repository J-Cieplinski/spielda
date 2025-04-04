#ifndef SPIELDA_GAME_COMPONENTS_TAGS_COLLISIONMASK_HPP
#define SPIELDA_GAME_COMPONENTS_TAGS_COLLISIONMASK_HPP

#include <bitset>

namespace spielda::tags
{

enum MaskLayer : std::uint64_t
{
    PLAYER = 1u << 0,
    ENEMY = 1u << 1,
    DECORATION = 1u << 2,
    WALL = 1u << 3,
    MOVING = 1u << 4,
    WEAPON = 1u << 5,
    PROJECTILE = 1u << 6,
};

inline constexpr std::bitset<8> ZERO_BITSET("00000000");

/*
 * Entities within the same mask do NOT collide with each other
 */
struct CollisionMask
{
    std::bitset<8> mask;
};

}  // namespace spielda::tags

#endif  // SPIELDA_GAME_COMPONENTS_TAGS_COLLISIONMASK_HPP
