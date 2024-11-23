#ifndef SPIELDA_GAME_COMPONENTS_TRANSFORM_HPP
#define SPIELDA_GAME_COMPONENTS_TRANSFORM_HPP

#include <raymath.h>

namespace spielda::components
{

struct Transform
{
    Vector2 position;
    Vector2 previousPosition;
    Vector2 scale;
    float rotation;
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_TRANSFORM_HPP
