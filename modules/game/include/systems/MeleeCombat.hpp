#ifndef SPIELDA_GAME_SYSTEMS_MELEECOMBAT_HPP
#define SPIELDA_GAME_SYSTEMS_MELEECOMBAT_HPP

#include <components/Weapon.hpp>
#include <events/Attack.hpp>

#include <entt/signal/dispatcher.hpp>
#include <roen/include/interfaces/ISystem.hpp>

namespace spielda::system
{

class MeleeCombat final : public roen::interfaces::ISystem
{
struct WeaponSwing
{
    components::Weapon weapon;
    entt::entity weaponEntity;
    Vector2 originalRelativePosition;
    double totalAnimationTime;
    double currentAnimationTime {0};
};
public:
    explicit MeleeCombat(entt::registry& entityManager, entt::dispatcher& eventDispatcher);
    void update(double dt);
private:
    void onAttack(events::Attack event);
    entt::dispatcher& eventDispatcher_;
    std::vector<WeaponSwing> swingsToAnimate_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_MELEECOMBAT_HPP