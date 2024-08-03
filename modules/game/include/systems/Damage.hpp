#ifndef SPIELDA_GAME_SYSTEMS_DAMAGE_HPP
#define SPIELDA_GAME_SYSTEMS_DAMAGE_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <events/Collision.hpp>

#include <entt/fwd.hpp>

namespace spielda::system
{

class Damage final : public roen::interfaces::ISystem
{
public:
    using CombatEntities = std::pair<entt::entity, entt::entity>; //Attacker, defender

    explicit Damage(entt::registry& entityManager, entt::dispatcher& eventDispatcher);
    void update();
private:
    void onCollision(events::Collision event);
    CombatEntities getCombatEntities(events::Collision event);

    entt::dispatcher& eventDispatcher_;
    std::vector<entt::entity> entitiesToDestroy_;
};

} // spielda::system


#endif //SPIELDA_GAME_SYSTEMS_DAMAGE_HPP