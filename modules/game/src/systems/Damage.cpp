#include <systems/Damage.hpp>

#include <components/Health.hpp>
#include <components/Weapon.hpp>

#include <roen/include/log/Logger.hpp>
#include <roen/include/log/formatters/entity.hpp>

#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

Damage::Damage(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{eventDispatcher}
{
    eventDispatcher_.sink<events::Collision>().connect<&Damage::onCollision>(this);
}

void Damage::onCollision(events::Collision event)
{
    auto [attacker, defender] = getCombatEntities(event);
    if(attacker == entt::null || defender == entt::null)
    {
        return;
    }

    auto& attackWeapon = entityManager_.get<components::Weapon>(attacker);
    
    if(!attackWeapon.attacking || attackWeapon.damagedEntities.contains(defender))
    {
        return;
    }

    auto& defenderHp = entityManager_.get<components::Health>(defender);
    defenderHp.currentHealth -= attackWeapon.damage;
    attackWeapon.damagedEntities.insert(defender);

    APP_INFO("Dealt {0} damage to entity {1}", attackWeapon.damage, defender);
    
    if(defenderHp.currentHealth <= 0)
    {
        APP_INFO("Entity {0} killed", defender);
        entityManager_.destroy(defender);
    }
}

Damage::CombatEntities Damage::getCombatEntities(events::Collision event)
{
    auto weaponView = entityManager_.view<components::Weapon>();

    auto isFirstEntityArmed = weaponView.contains(event.firstCollider);
    auto isSecondEntityArmed = weaponView.contains(event.secondCollider);

    if(!(isFirstEntityArmed || isSecondEntityArmed))
    {
        return {entt::null, entt::null};
    }

    entt::entity attacker {entt::null};
    entt::entity defender {entt::null};

    weaponView.each([&attacker, &event](entt::entity entity, components::Weapon weapon) {
        if(weapon.attacking && (entity == event.firstCollider || entity == event.secondCollider))
        {
            attacker = entity;
            return;
        }
    });


    auto healthView = entityManager_.view<components::Health>();
    healthView.each([&defender, &event](entt::entity entity, components::Health health) {
        if(entity == event.firstCollider || entity == event.secondCollider)
        {
            defender = entity;
            return;
        }
    });

    return {attacker, defender};
}

} // namespace spielda::system
