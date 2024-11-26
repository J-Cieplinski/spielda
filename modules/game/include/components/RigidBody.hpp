#ifndef SPIELDA_GAME_COMPONENTS_RIGIDBODY_HPP
#define SPIELDA_GAME_COMPONENTS_RIGIDBODY_HPP

#include <raymath.h>

namespace spielda::components
{

struct RigidBody
{
    Vector2 velocity;
    Vector2 lastVelocity;
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_RIGIDBODY_HPP
