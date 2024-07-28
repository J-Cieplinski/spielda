#include <systems/MeleeCombat.hpp>

#include <components/Transform.hpp>

#include <entt/entity/registry.hpp>

#include <ranges>

namespace spielda::system
{

MeleeCombat::MeleeCombat(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{eventDispatcher}
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
    const auto view = entityManager_.view<components::Transform, components::Weapon>();
    for(auto& swing : swingsToAnimate_)
    {
        auto& weaponTransform = view.get<components::Transform>(swing.weaponEntity);
        weaponTransform.rotation = 90.f * (swing.currentAnimationTime / swing.totalAnimationTime);

        swing.currentAnimationTime += dt;
        if(swing.totalAnimationTime <= swing.currentAnimationTime)
        {
            swingsToClear.push_back(swing);

            auto& weapon = view.get<components::Weapon>(swing.weaponEntity);
            weapon.originPosition = swing.originalRelativePosition;
            weaponTransform.rotation = 0;
            weapon.attacking = false;
            weapon.damagedEntities.clear();
        }
    }

    std::erase_if(swingsToAnimate_, [&swingsToClear](WeaponSwing& swing){
        auto it = std::ranges::find_if(swingsToClear, [&swing](WeaponSwing& swingToClear) {
            return swingToClear.weaponEntity == swing.weaponEntity;
        });

        return it != swingsToClear.end();
    });
}

} // spielda::system