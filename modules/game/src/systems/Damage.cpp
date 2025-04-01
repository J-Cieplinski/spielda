#include <systems/Damage.hpp>

#include <SpatialGrid.hpp>

#include <components/CharacterSheet.hpp>
#include <components/Health.hpp>
#include <components/Projectile.hpp>
#include <components/Spell.hpp>
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

    std::int32_t damage{0};

    if (event.collisionType == CollisionType::WEAPON)
    {
        auto& attackWeapon = entityManager_.get<components::Weapon>(attacker);
        auto& attackerSheet = entityManager_.get<components::CharacterSheet>(attackWeapon.wielder);

        if (!attackWeapon.attacking || attackWeapon.damagedEntities.contains(defender))
        {
            return;
        }

        damage = attackWeapon.damage + attackerSheet.strength;
        attackWeapon.damagedEntities.insert(defender);
    }
    else if (event.collisionType == CollisionType::PROJECTILE)
    {
        const auto& projectile = entityManager_.get<components::Projectile>(attacker);

        damage = projectile.damage;
    }

    auto& defenderHp = entityManager_.get<components::Health>(defender);

    defenderHp.currentHealth -= damage;

    APP_INFO("Dealt {0} damage to entity {1}", damage, defender);

    if (defenderHp.currentHealth <= 0)
    {
        APP_INFO("Entity {0} killed", defender);
        entitiesToDestroy_.insert(defender);
    }
}

Damage::CombatEntities Damage::getCombatEntities(events::Collision event)
{
    if (event.collisionType != CollisionType::WEAPON
        && event.collisionType != CollisionType::PROJECTILE)
    {
        return {entt::null, entt::null};
    }

    auto entities = getMeleeAttacker(event);

    if (entities.first == entt::null)
    {
        entities = getRangedAttacker(event);

        if (entities.first == entt::null)
        {
            return {entt::null, entt::null};
        }
    }

    const auto healthView = entityManager_.view<components::Health>();
    healthView.each(
        [&entities, &event](const entt::entity entity, components::Health)
        {
            if (entity == event.firstCollider || entity == event.secondCollider)
            {
                entities.second = entity;
            }
        });

    return entities;
}

Damage::CombatEntities Damage::getMeleeAttacker(events::Collision event)
{
    const auto weaponView = entityManager_.view<components::Weapon>();

    for (const auto& [entity, weapon] : weaponView.each())
    {
        if (weapon.attacking)
        {
            if (entity == event.firstCollider)
            {
                return {event.firstCollider, entt::null};
            }
            else if (entity == event.secondCollider)
            {
                return {event.secondCollider, entt::null};
            }
        }
    }

    return {entt::null, entt::null};
}

Damage::CombatEntities Damage::getRangedAttacker(events::Collision event)
{
    const auto projectileView = entityManager_.view<components::Projectile>();

    if (auto it = projectileView.find(event.firstCollider); it != projectileView.end())
    {
        return {event.firstCollider, entt::null};
    }
    else if (auto it = projectileView.find(event.secondCollider); it != projectileView.end())
    {
        return {event.secondCollider, entt::null};
    }

    return {entt::null, entt::null};
}

}  // namespace spielda::system
