#include <systems/ProjectileSpawner.hpp>

#include <SpatialGrid.hpp>

#include <components/Animation.hpp>
#include <components/Collider.hpp>
#include <components/RigidBody.hpp>
#include <components/Spell.hpp>
#include <components/Sprite.hpp>
#include <components/Transform.hpp>
#include <components/tags/CollisionMask.hpp>

#include <entt/entity/registry.hpp>

namespace spielda::system
{

ProjectileSpawner::ProjectileSpawner(entt::registry& entityManager,
                                     entt::dispatcher& eventDispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{eventDispatcher}
{
    eventDispatcher.sink<events::Attack>().connect<&ProjectileSpawner::onAttack>(this);
}

void ProjectileSpawner::onAttack(events::Attack event)
{
    auto group = entityManager_.group<components::Spell>(
        entt::get<components::Sprite, components::Transform, components::RigidBody,
                  tags::CollisionMask>);

    if (not group.contains(event.attacker))
    {
        return;
    }

    auto currentTime = GetTime();

    auto [spell, sprite, transform, rigidBody, mask]
        = group.get<components::Spell, components::Sprite, components::Transform,
                    components::RigidBody, tags::CollisionMask>(event.attacker);

    if (const auto it = lastSpawnTimePerEntity_.find(event.attacker);
        it != lastSpawnTimePerEntity_.end())
    {
        if (currentTime - it->second <= spell.spawnFrequency)
        {
            return;
        }
    }

    spawnEntity(spell, sprite, transform, rigidBody, mask, currentTime);

    lastSpawnTimePerEntity_[event.attacker] = currentTime;
}

void ProjectileSpawner::spawnEntity(components::Spell spell, components::Sprite sprite,
                                    components::Transform transform,
                                    components::RigidBody rigidBody,
                                    tags::CollisionMask collisionMask, double currentTime) const
{
    auto projectile = entityManager_.create();

    Vector2 spellVelocity{
        .x = spell.velocity.x * rigidBody.lastVelocity.x,
        .y = spell.velocity.y * rigidBody.lastVelocity.y,
    };
    auto spellSourceRectangle = spell.srcRect;
    auto spellTransform = transform;

    if (spellVelocity.x < 0)
    {
        spellTransform.rotation = -90;
    }
    else if (spellVelocity.x > 0)
    {
        spellTransform.rotation = 90;
    }
    else if (spellVelocity.y > 0)
    {
        spellSourceRectangle.height *= -1;
    }

    components::Sprite spellSprite{
        .size = spell.size,
        .origin = spell.origin,
        .srcRect = spellSourceRectangle,
        .layer = sprite.layer,
        .zIndexInLayer = sprite.zIndexInLayer,
        .guid = spell.guid,
        .isFixed = false,
    };

    components::BoxCollider spellCollider{
        .position = transform.position - sprite.size / 2,
        .previousPosition = transform.previousPosition,
        .size = sprite.size,
        .collisionType = CollisionType::WEAPON,
    };

    components::Animation spellAnimation{
        .numberOfFrames = 4,
        .currentFrame = 0,
        .frameRateSpeed = 10,
        .shouldLoop = true,
        .startTime = currentTime,
        .type = components::AnimationType::HORIZONTAL,
    };

    collisionMask.mask |= tags::PROJECTILE;
    collisionMask.mask &= ~tags::MOVING;

    entityManager_.emplace<components::Animation>(projectile, spellAnimation);
    entityManager_.emplace<components::RigidBody>(projectile, spellVelocity, Vector2{0, 0});
    entityManager_.emplace<components::Transform>(projectile, spellTransform);
    entityManager_.emplace<components::Sprite>(projectile, spellSprite);
    entityManager_.emplace<components::Collider>(projectile, spellCollider);
    entityManager_.emplace<tags::CollisionMask>(projectile, collisionMask);

    entityManager_.ctx().get<SpatialGrid>().updateEntityPosition(projectile, spellCollider.position,
                                                                 spellCollider.previousPosition);
}

}  // namespace spielda::system