#ifndef SPIELDA_GAME_COMPONENTS_AI_HPP
#define SPIELDA_GAME_COMPONENTS_AI_HPP

#include <raylib.h>

namespace spielda::components
{

enum class AIState
{
    IDLE,
    FOLLOWING,
    ATTACKING,
    RETURNING
};

struct AI
{
    float detectRadius;
    AIState state {AIState::IDLE};
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_AI_HPP
