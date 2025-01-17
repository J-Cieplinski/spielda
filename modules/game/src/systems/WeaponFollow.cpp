#include <systems/WeaponFollow.hpp>

#include <components/Weapon.hpp>
#include <components/WieldedWeapon.hpp>

#include <entt/entt.hpp>
#include <raymath.h>

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
        std::visit([&](auto& weaponCol, auto& wielderCol) {
            weaponCol.previousPosition = weaponCol.position;
            weaponCol.position = wielderCol.position + wieldedWeapon.colliderAttachOffset;
        }, weaponCollider, wielderCollider);
    }
}

} // spielda::system
