#include <systems/Collision.hpp>

#include <components/BoxCollider.hpp>
#include <components/CircleCollider.hpp>
#include <components/tags/CollisionMask.hpp>
#include <events/Collision.hpp>

#include <roen/include/log/Logger.hpp>
#include <roen/include/log/formatters/entity.hpp>

#include <entt/entt.hpp>

namespace spielda::system
{

Collision::Collision(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{eventDispatcher}
{
}

void Collision::update() const
{
    constexpr std::uint8_t WEAPON_BIT{5};

    const auto& boxView = entityManager_.view<components::BoxCollider>();
    const auto& circleView = entityManager_.view<components::CircleCollider>();
    const auto& maskView = entityManager_.view<tags::CollisionMask>();
    boxView.each([](components::BoxCollider& collider) { collider.collisionType = CollisionType::NONE; });
    circleView.each([](components::CircleCollider& collider) { collider.collisionType = CollisionType::NONE; });

    for(auto& entity : circleView)
    {
        auto& entityCollider = circleView.get<components::CircleCollider>(entity);
        const auto entityMask = maskView.get<tags::CollisionMask>(entity);

        boxView.each([this, &maskView, &entityCollider, &entityMask, entity](const entt::entity boxEntity, components::BoxCollider& collider)
        {
            const auto boxMask = maskView.get<tags::CollisionMask>(boxEntity);
            if((entityMask.mask & boxMask.mask) != tags::ZERO_BITSET)
            {
                return;
            }

            if (CheckCollisionCircleRec(entityCollider.position, entityCollider.radius, collider))
            {
                const auto isBoxEntityAWeapon = boxMask.mask.test(WEAPON_BIT);

                APP_TRACE("Entity {0} collided with Entity {1}", entity, boxEntity);
                const auto collisionType = isBoxEntityAWeapon ? CollisionType::WEAPON : CollisionType::WALL;
                entityCollider.collisionType = collisionType;
                collider.collisionType = collisionType;
                eventDispatcher_.enqueue(events::Collision{entity, boxEntity, collisionType});
            }
        });
    }

    eventDispatcher_.update<events::Collision>();
}

} // spielda::system
