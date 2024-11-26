#include <systems/ProjectileSpawner.hpp>

#include <components/BoxCollider.hpp>
#include <components/CircleCollider.hpp>
#include <components/RigidBody.hpp>
#include <components/Spell.hpp>
#include <components/Sprite.hpp>
#include <components/Transform.hpp>
#include <components/tags/CollisionMask.hpp>

namespace spielda::system
{

ProjectileSpawner::ProjectileSpawner(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{eventDispatcher}
{
    eventDispatcher.sink<events::Attack>().connect<&ProjectileSpawner::onAttack>(this);
}

void ProjectileSpawner::onAttack(events::Attack event)
{
    auto attacker = event.attacker;
    auto [spell, sprite, transform, rigidBody, mask] = entityManager_.get<components::Spell, components::Sprite, components::Transform, components::RigidBody, tags::CollisionMask>(attacker);

    auto projectile = entityManager_.create();

    Vector2 spellVelocity {
        .x = rigidBody.lastVelocity.x != 0 ? spell.velocity.x * rigidBody.lastVelocity.x : 0,
        .y = rigidBody.lastVelocity.y != 0 ? spell.velocity.y * rigidBody.lastVelocity.y : 0,
    };
    auto spellSourceRectangle = spell.srcRect;
    auto spellTransform = transform;

    if(spellVelocity.x < 0)
    {
        spellTransform.rotation = -90;
    }
    else if(spellVelocity.x > 0)
    {
        spellTransform.rotation = 90;
    }
    else if(spellVelocity.y > 0)
    {
        spellSourceRectangle.height *= -1;
    }

    components::Sprite spellSprite
    {
        .size = spell.size,
        .origin = spell.origin,
        .srcRect = spellSourceRectangle,
        .layer = sprite.layer,
        .zIndexInLayer = sprite.zIndexInLayer,
        .guid = spell.guid,
        .isFixed = false
    };

    components::BoxCollider spellCollider {
        .position = transform.position - sprite.size / 2,
        .previousPosition = transform.previousPosition,
        .size = sprite.size,
        .collisionType = CollisionType::WEAPON
    };

    entityManager_.emplace<components::RigidBody>(projectile, spellVelocity, Vector2{0, 0});
    entityManager_.emplace<components::Transform>(projectile, spellTransform);
    entityManager_.emplace<components::Sprite>(projectile, spellSprite);
    entityManager_.emplace<components::BoxCollider>(projectile, spellCollider);
    entityManager_.emplace<tags::CollisionMask>(projectile, mask);
}

} // namespace spielda::system