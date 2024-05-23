#include <game/systems/MeleeCombat.hpp>

#include <game/components/Transform.hpp>

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
        if(attackerWeapon->attacking)
        {
            return;
        }
        
        attackerWeapon->attacking = true;
        WeaponSwing swing {
            .weapon = *attackerWeapon,
            .weaponEntity = event.attacker,
            .originalRelativePosition = attackerWeapon->originPosition,
            .totalAnimationTime = 0.5f,
            .currentAnimationTime = 0.f
        };

        swingsToAnimate_.emplace_back(swing);
    }
}

void MeleeCombat::update(double dt)
{
    std::vector<WeaponSwing> swingsToClear {};
    for(auto& swing : swingsToAnimate_)
    {
        auto& weaponTransform = entityManager_.get<components::Transform>(swing.weaponEntity);
        weaponTransform.rotation = 90 * (swing.currentAnimationTime / swing.totalAnimationTime);

        swing.currentAnimationTime += dt;
        if(swing.totalAnimationTime <= swing.currentAnimationTime)
        {
            swingsToClear.push_back(swing);

            auto& weapon = entityManager_.get<components::Weapon>(swing.weaponEntity);
            weapon.originPosition = swing.originalRelativePosition;
            weaponTransform.rotation = 0;
            weapon.attacking = false;
        }
    }

    std::erase_if(swingsToAnimate_, [&swingsToClear](WeaponSwing& swing){
        auto it = std::find_if(swingsToClear.begin(), swingsToClear.end(), [&swing](WeaponSwing& swingToClear) {
            return swingToClear.weaponEntity == swing.weaponEntity;
        });

        return it != swingsToClear.end();
    });
}

} // spielda::system