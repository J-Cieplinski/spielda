#ifndef SPIELDA_GAME_COMPONENTS_BOXCOLLIDER_HPP
#define SPIELDA_GAME_COMPONENTS_BOXCOLLIDER_HPP

#include <Utils.hpp>

#include <raylib.h>

namespace spielda::components
{

struct BoxCollider
{
    Vector2 position;
    Vector2 previousPosition;
    Vector2 size;
    CollisionType collisionType;

    operator Rectangle() const
    {
        return {
            .x = position.x,
            .y = position.y,
            .width = size.x,
            .height = size.y
        };
    }
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_BOXCOLLIDER_HPP
