#ifndef SPIELDA_GAME_SYSTEMS_MELEECOMBAT_HPP
#define SPIELDA_GAME_SYSTEMS_MELEECOMBAT_HPP

#include <game/components/Weapon.hpp>
#include <game/events/Attack.hpp>

#include <entt/signal/dispatcher.hpp>
#include <roen/interfaces/ISystem.hpp>

namespace spielda::system
{

class MeleeCombat final : public roen::interfaces::ISystem
{
struct WeaponSwing
{
    components::Weapon weapon;
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