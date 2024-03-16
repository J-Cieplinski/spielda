#ifndef SPIELDA_GAME_COMPONENTS_BOXCOLLIDER_HPP
#define SPIELDA_GAME_COMPONENTS_BOXCOLLIDER_HPP

#include <raylib.h>

namespace spielda::components
{

struct BoxCollider
{
    Vector2 position;
    Vector2 size;
    bool isColliding;
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_BOXCOLLIDER_HPP
