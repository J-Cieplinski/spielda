#include <systems/Collision.hpp>

#include <components/BoxCollider.hpp>
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

    const auto& view = entityManager_.view<components::BoxCollider>();
    const auto& maskView = entityManager_.view<tags::CollisionMask>();
    view.each([](components::BoxCollider& collider) { collider.collisionType = components::CollisionType::NONE; });

    for (auto entityIt = view.begin(); entityIt != view.end(); ++entityIt)
    {
        auto& entityOneCollider = view.get<components::BoxCollider>(*entityIt);
        const auto maskOne = maskView.get<tags::CollisionMask>(*entityIt);
        const auto isEntityOneAWeapon = maskOne.mask.test(WEAPON_BIT);

        for (auto it2 = entityIt + 1; it2 != view.end(); ++it2) {
            auto& entityTwoCollider = view.get<components::BoxCollider>(*it2);
            const auto maskTwo = maskView.get<tags::CollisionMask>(*it2);

            if((maskOne.mask & maskTwo.mask) != 0)
            {
                continue;
            }

            const auto isEntityTwoAWeapon = maskTwo.mask.test(WEAPON_BIT);

            if (CheckCollisionRecs(entityOneCollider, entityTwoCollider)) {

                APP_TRACE("Entity {0} collided with Entity {1}", *entityIt, *it2);
                entityOneCollider.collisionType = isEntityTwoAWeapon || isEntityOneAWeapon ? components::CollisionType::WEAPON : components::CollisionType::WALL;
                entityTwoCollider.collisionType = isEntityTwoAWeapon || isEntityOneAWeapon ? components::CollisionType::WEAPON : components::CollisionType::WALL;
                eventDispatcher_.enqueue(events::Collision{*entityIt, *it2});
            }
        }
    }

    eventDispatcher_.update<events::Collision>();
}

} // spielda::system
