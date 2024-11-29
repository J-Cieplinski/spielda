#ifndef SPIELDA_GAME_SYSTEMS_PROJECTILESPAWNER_HPP
#define SPIELDA_GAME_SYSTEMS_PROJECTILESPAWNER_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <events/Attack.hpp>

#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

class ProjectileSpawner final : public roen::interfaces::ISystem
{
public:
    explicit ProjectileSpawner(entt::registry& entityManager, entt::dispatcher& eventDispatcher);
private:
    void onAttack(events::Attack event);
    entt::dispatcher& eventDispatcher_;
    std::map<entt::entity, double> lastSpawnTimePerEntity_;
};

} // spielda::system



#endif //SPIELDA_GAME_SYSTEMS_PROJECTILESPAWNER_HPP