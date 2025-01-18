#include <systems/CollisionPartitioned.hpp>

#include <SpatialGrid.hpp>
#include <components/tags/CollisionMask.hpp>
#include <events/Collision.hpp>

#include <entt/entt.hpp>

#include <type_traits>

namespace spielda::system
{

CollisionPartitioned::CollisionPartitioned(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{eventDispatcher}
{
}

void CollisionPartitioned::update() const
{
    const auto& colliderView = entityManager_.view<components::Collider>();
    const auto& maskView = entityManager_.view<tags::CollisionMask>();

    colliderView.each([](components::Collider& collider) {
        std::visit([](auto& collider) {
            collider.collisionType = CollisionType::NONE;
        }, collider);
    });

    const auto* grid = entityManager_.ctx().find<SpatialGrid>();
    if(grid == nullptr)
    {
        APP_ERROR("No SpatialPartition grid present. Quitting collision detection");
        return;
    }
    
    for (const auto& [cellIndex, entities] : *grid)
    {
        for (auto entityA : entities)
        {
            constexpr std::bitset<8> DECORATION_MASK{tags::MaskLayer::WALL};
            const auto& maskA = maskView.get<tags::CollisionMask>(entityA);

            if((maskA.mask & DECORATION_MASK).any())
            {
                continue;
            }

            auto& entityACollider = colliderView.get<components::Collider>(entityA);
            // Get neighboring cells including the current cell
            auto neighbors = grid->getNeighboringCells(getColliderPosition(entityACollider));
            for (auto neighborIndex : neighbors)
            {
                const auto& neighborEntities = grid->at(neighborIndex);
                if(not neighborEntities.has_value())
                {
                    continue;
                }

                for (auto entityB : neighborEntities->get())
                {
                    if (entityA == entityB)
                    {
                        continue; // Avoid self-collision
                    }

                    auto& entityBCollider = colliderView.get<components::Collider>(entityB);
                    const auto& maskB = maskView.get<tags::CollisionMask>(entityB);

                    // Apply collision mask filtering
                    if((maskA.mask & maskB.mask).any())
                    {
                        continue;
                    }
                    
                    // Check collision
                    if (checkCollision(entityACollider, entityBCollider))
                    {
                        constexpr std::bitset<8> WEAPON_MASK{tags::MaskLayer::WEAPON};
                        const auto isAnyEntityAWeapon = ((maskA.mask | maskB.mask) & WEAPON_MASK).any();
                        APP_INFO("Entity {0} collided with Entity {1}", entityA, entityB);
                        const auto collisionType = isAnyEntityAWeapon ? CollisionType::WEAPON : CollisionType::WALL;
                        
                        std::visit([&collisionType](auto& colliderA, auto& colliderB)
                        {
                            colliderA.collisionType = collisionType;
                            colliderB.collisionType = collisionType;
                        }, entityACollider, entityBCollider);

                        eventDispatcher_.enqueue(events::Collision {
                            .firstCollider = entityA,
                            .secondCollider = entityB,
                            .collisionType = collisionType});                            
                    }
                }
            }
        }
    }

    eventDispatcher_.update<events::Collision>();
}

Vector2 CollisionPartitioned::getColliderPosition(const components::Collider& collider) const
{
    return std::visit([](const auto& col) {
        return col.position;
    }, collider);
}

bool CollisionPartitioned::checkCollision(const components::Collider& colliderA, const components::Collider& colliderB) const
{
    if (std::holds_alternative<components::CircleCollider>(colliderA) && std::holds_alternative<components::CircleCollider>(colliderB))
    {
        const auto& colA = std::get<components::CircleCollider>(colliderA);
        const auto& colB = std::get<components::CircleCollider>(colliderB);
        return CheckCollisionCircles(colA.position, colA.radius, colB.position, colB.radius);
    }
    else if (std::holds_alternative<components::BoxCollider>(colliderA) && std::holds_alternative<components::BoxCollider>(colliderB))
    {
        return CheckCollisionRecs(std::get<components::BoxCollider>(colliderA), std::get<components::BoxCollider>(colliderB));
    }
    else
    {
        return checkCircleBoxCollision(colliderA, colliderB);
    }
}

bool CollisionPartitioned::checkCircleBoxCollision(const components::Collider& colliderA, const components::Collider& colliderB) const
{
    const components::CircleCollider* circle {nullptr};
    const components::BoxCollider* box {nullptr};

    if(std::holds_alternative<components::CircleCollider>(colliderA))
    {
        circle = &std::get<components::CircleCollider>(colliderA);
        box = &std::get<components::BoxCollider>(colliderB);
    }
    else
    {
        circle = &std::get<components::CircleCollider>(colliderB);
        box = &std::get<components::BoxCollider>(colliderA);
    }

    return CheckCollisionCircleRec(circle->position, circle->radius, *box);
}

} // namespace spielda::system