#ifndef SPIELDA_GAME_SYSTEMS_RANGEDCOMBAT_HPP
#define SPIELDA_GAME_SYSTEMS_RANGEDCOMBAT_HPP

#include <components/tags/CollisionMask.hpp>
#include <events/Collision.hpp>

#include <entt/signal/dispatcher.hpp>
#include <roen/include/interfaces/ISystem.hpp>

namespace spielda::system
{

class RangedCombat final : public roen::interfaces::ISystem
{
public:
    RangedCombat(entt::registry& entityManager, entt::dispatcher& eventDispatcher);
    void update(double dt);

private:
    void onHit(events::Collision event);
    entt::dispatcher& eventDispatcher_;
    std::set<entt::entity> entitiesToDestroy_;
};

}  // namespace spielda::system

#endif  // SPIELDA_GAME_SYSTEMS_RANGEDCOMBAT_HPP