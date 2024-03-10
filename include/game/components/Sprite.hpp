#ifndef SPIELDA_GAME_COMPONENTS_SPRITE_HPP
#define SPIELDA_GAME_COMPONENTS_SPRITE_HPP

#include <raylib.h>

#include <cstdint>

namespace spielda::components
{

struct Sprite
{
    Vector2 size;
    Rectangle srcRect;
    std::uint32_t layer;
    std::uint32_t zIndexInLayer;
    std::uint64_t guid;
    bool isFixed;
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_SPRITE_HPP
