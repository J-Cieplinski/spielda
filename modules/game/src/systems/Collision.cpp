#include <systems/Collision.hpp>

#include <components/BoxCollider.hpp>
#include <components/tags/CollisionMask.hpp>
#include <events/Collision.hpp>

#include <roen/include/log/Logger.hpp>

#include <entt/entt.hpp>

namespace spielda::system
{

Collision::Collision(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{eventDispatcher}
{
}

void Collision::update()
{
    const auto& view = entityManager_.view<components::BoxCollider>();
    view.each([](components::BoxCollider& collider) { collider.isColliding = false; });

    for (auto entityIt = view.begin(); entityIt < view.end(); ++entityIt)
    {
        for (auto it2 = entityIt + 1; it2 < view.end(); ++it2) {
            auto &entityOneCollider = view.get<components::BoxCollider>(*entityIt);
            auto &entityTwoCollider = view.get<components::BoxCollider>(*it2);

            if (CheckCollisionRecs(entityOneCollider, entityTwoCollider)) {
                const auto* maskOne = entityManager_.try_get<tags::CollisionMask>(*entityIt);
                const auto* maskTwo = entityManager_.try_get<tags::CollisionMask>(*it2);

                if((maskOne && maskTwo)
                    && ((maskOne->mask & maskTwo->mask) != 0))
                {
                    continue;
                }

                APP_TRACE("Entity {0} collided with Entity {1}", static_cast<std::uint32_t>(*entityIt),
                            static_cast<std::uint32_t>(*it2));
                entityOneCollider.isColliding = true;
                entityTwoCollider.isColliding = true;
                eventDispatcher_.enqueue(events::Collision{*entityIt, *it2});
            }
        }
    }

    eventDispatcher_.update<events::Collision>();
}

} // spielda::system