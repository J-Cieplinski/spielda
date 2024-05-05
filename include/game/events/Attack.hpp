#ifndef SPIELDA_GAME_EVENTS_ATTACK_HPP
#define SPIELDA_GAME_EVENTS_ATTACK_HPP

#include <entt/entity/entity.hpp>

namespace spielda::events
{

struct Attack
{
    entt::entity attacker;
    entt::entity target;
};

} // spielda::events

#endif //SPIELDA_GAME_EVENTS_ATTACK_HPP
