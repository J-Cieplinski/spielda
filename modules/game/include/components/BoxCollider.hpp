#ifndef SPIELDA_GAME_COMPONENTS_BOXCOLLIDER_HPP
#define SPIELDA_GAME_COMPONENTS_BOXCOLLIDER_HPP

#include <raylib.h>

namespace spielda::components
{

enum class CollisionType
{
    WEAPON,
    WALL,
    NONE
};

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
