#include <systems/Damage.hpp>

#include <SpatialGrid.hpp>

#include <components/CharacterSheet.hpp>
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
    , entitiesToDestroy_{}
{
    eventDispatcher_.sink<events::Collision>().connect<&Damage::onCollision>(this);
}

void Damage::update()
{
    if (entitiesToDestroy_.empty())
    {
        return;
    }

    auto& grid = entityManager_.ctx().get<SpatialGrid>();
    grid.removeEntities(entitiesToDestroy_);
    entityManager_.destroy(entitiesToDestroy_.begin(), entitiesToDestroy_.end());
    entitiesToDestroy_.clear();
}

void Damage::onCollision(events::Collision event)
{
    auto [attacker, defender] = getCombatEntities(event);
    if (attacker == entt::null || defender == entt::null)
    {
        return;
    }

    auto& attackWeapon = entityManager_.get<components::Weapon>(attacker);
    auto& attackerSheet = entityManager_.get<components::CharacterSheet>(attackWeapon.wielder);

    if (!attackWeapon.attacking || attackWeapon.damagedEntities.contains(defender))
    {
        return;
    }

    auto& defenderHp = entityManager_.get<components::Health>(defender);

    const auto damage = attackWeapon.damage + attackerSheet.strength;
    defenderHp.currentHealth -= damage;
    attackWeapon.damagedEntities.insert(defender);

    APP_INFO("Dealt {0} damage to entity {1}", damage, defender);

    if (defenderHp.currentHealth <= 0)
    {
        APP_INFO("Entity {0} killed", defender);
        entitiesToDestroy_.insert(defender);
    }
}

Damage::CombatEntities Damage::getCombatEntities(events::Collision event)
{
    if (event.collisionType != CollisionType::WEAPON)
    {
        return {entt::null, entt::null};
    }

    const auto weaponView = entityManager_.view<components::Weapon>();

    const auto isFirstEntityArmed = weaponView.contains(event.firstCollider);
    const auto isSecondEntityArmed = weaponView.contains(event.secondCollider);

    if (!(isFirstEntityArmed || isSecondEntityArmed))
    {
        return {entt::null, entt::null};
    }

    entt::entity attacker{entt::null};
    entt::entity defender{entt::null};

    weaponView.each(
        [&attacker, &event](const entt::entity entity, const components::Weapon& weapon)
        {
            if (weapon.attacking
                && (entity == event.firstCollider || entity == event.secondCollider))
            {
                attacker = entity;
            }
        });

    const auto healthView = entityManager_.view<components::Health>();
    healthView.each(
        [&defender, &event](const entt::entity entity, components::Health)
        {
            if (entity == event.firstCollider || entity == event.secondCollider)
            {
                defender = entity;
            }
        });

    return {attacker, defender};
}

}  // namespace spielda::system
