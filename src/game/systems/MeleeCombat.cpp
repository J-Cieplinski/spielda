#include <game/systems/MeleeCombat.hpp>

#include <entt/entity/registry.hpp>

namespace spielda::system
{

MeleeCombat::MeleeCombat(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem(entityManager)
    , eventDispatcher_(eventDispatcher)
{
    eventDispatcher.sink<events::Attack>().connect<&MeleeCombat::onAttack>(this);
}

void MeleeCombat::onAttack(events::Attack event)
{
    if(auto* attackerWeapon = entityManager_.try_get<components::Weapon>(event.attacker))
    {
        WeaponSwing swing {
            .weapon = *attackerWeapon,
            .originalRelativePosition = attackerWeapon->relativePosition
        };

        swingsToAnimate_.emplace_back(swing);
    }
}

void MeleeCombat::update(double dt)
{
    std::vector<WeaponSwing> swingsToClear {};
    for(auto& swing : swingsToAnimate_)
    {
        /*
         * Add weapon swing animation here
         */

        swing.currentAnimationTime += dt;
        if(swing.totalAnimationTime <= swing.currentAnimationTime)
        {
            swingsToClear.push_back(swing);

            auto& weapon = entityManager_.get<components::Weapon>(swing.weapon.parentEntity);
            weapon.relativePosition = swing.originalRelativePosition;
        }
    }

    std::erase_if(swingsToAnimate_, [&swingsToClear](WeaponSwing& swing){
        auto it = std::find_if(swingsToClear.begin(), swingsToClear.end(), [&swing](WeaponSwing& swingToClear) {
            return swingToClear.weapon.parentEntity == swing.weapon.parentEntity;
        });

        return it != swingsToClear.end();
    });
}

} // spielda::system