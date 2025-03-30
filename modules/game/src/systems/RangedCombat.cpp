#include <systems/RangedCombat.hpp>

#include <SpatialGrid.hpp>

#include <components/Transform.hpp>

#include <entt/entity/registry.hpp>

#include <ranges>

namespace spielda::system
{

RangedCombat::RangedCombat(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{eventDispatcher}
{
    eventDispatcher.sink<events::Collision>().connect<&RangedCombat::onHit>(this);
}

void RangedCombat::onHit(events::Collision event)
{
    if (event.collisionType != CollisionType::PROJECTILE)
    {
        return;
    }

    const auto& maskView = entityManager_.view<tags::CollisionMask>();
    auto entityAMask = maskView.get<tags::CollisionMask>(event.firstCollider);

    constexpr std::bitset<8> PROJECTILE_MASK{tags::MaskLayer::PROJECTILE};
    const auto isEntityAProjectile = (entityAMask.mask & PROJECTILE_MASK).any();

    const auto projectileEntity = isEntityAProjectile ? event.firstCollider : event.secondCollider;

    entitiesToDestroy_.insert(projectileEntity);
}

void RangedCombat::update(double dt)
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

}  // namespace spielda::system