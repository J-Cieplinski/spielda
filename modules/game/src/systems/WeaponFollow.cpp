#include <systems/WeaponFollow.hpp>

#include <SpatialGrid.hpp>

#include <components/Weapon.hpp>
#include <components/WieldedWeapon.hpp>

#include <raymath.h>
#include <entt/entt.hpp>

namespace spielda::system
{

WeaponFollow::WeaponFollow(entt::registry& entityManager)
    : ISystem{entityManager}
{
}

void WeaponFollow::update() const
{
    auto wielderView = entityManager_.view<components::WieldedWeapon, components::Collider>();
    auto weaponView = entityManager_.view<components::Weapon, components::Collider>();

    for (const auto& [wielder, wieldedWeapon, wielderCollider] : wielderView.each())
    {
        auto& weaponCollider = weaponView.get<components::Collider>(wieldedWeapon.weaponEntity);
        std::visit(
            [&](auto& weaponCol, auto& wielderCol)
            {
                weaponCol.previousPosition = weaponCol.position;
                weaponCol.position = wielderCol.position + wieldedWeapon.colliderAttachOffset;
                entityManager_.ctx().get<SpatialGrid>().updateEntityPosition(
                    wieldedWeapon.weaponEntity, weaponCol.previousPosition, weaponCol.position);
            },
            weaponCollider, wielderCollider);
    }
}

}  // namespace spielda::system
