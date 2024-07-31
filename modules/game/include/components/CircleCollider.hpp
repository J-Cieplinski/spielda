#ifndef SPIELDA_GAME_COMPONENTS_CIRCLECOLLIDER_HPP
#define SPIELDA_GAME_COMPONENTS_CIRCLECOLLIDER_HPP

#include <Utils.hpp>

#include <raylib.h>

namespace spielda::components
{

struct CircleCollider
{
    Vector2 position;
    Vector2 previousPosition;
    float radius;
    CollisionType collisionType;
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_CIRCLECOLLIDER_HPP