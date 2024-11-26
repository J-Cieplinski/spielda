#ifndef SPIELDA_GAME_COMPONENTS_SPELL_HPP
#define SPIELDA_GAME_COMPONENTS_SPELL_HPP

#include <raymath.h>

namespace spielda::components
{

struct Spell
{
    Vector2 velocity;
    Vector2 size;
    Vector2 origin;
    Rectangle srcRect;
    float damage;
    std::uint64_t guid;
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_RIGIDBODY_HPP
