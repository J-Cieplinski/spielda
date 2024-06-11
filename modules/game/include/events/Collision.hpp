#ifndef SPIELDA_GAME_EVENTS_COLLISION_HPP
#define SPIELDA_GAME_EVENTS_COLLISION_HPP

#include <entt/entity/entity.hpp>

namespace spielda::events
{

struct Collision
{
    entt::entity firstCollider;
    entt::entity secondCollider;
};

} // spielda::events

#endif //SPIELDA_GAME_EVENTS_COLLISION_HPP
