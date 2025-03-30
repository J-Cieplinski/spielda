#ifndef SPIELDA_GAME_EVENTS_AIDETECTEDENEMY_HPP
#define SPIELDA_GAME_EVENTS_AIDETECTEDENEMY_HPP

#include <raylib.h>

#include <entt/entity/entity.hpp>

namespace spielda::events
{

struct AIDetectedEnemy
{
    Vector2 detectedEntityPosition;
    entt::entity aiEntity;
};

}  // namespace spielda::events

#endif  // SPIELDA_GAME_EVENTS_AIDETECTEDENEMY_HPP
