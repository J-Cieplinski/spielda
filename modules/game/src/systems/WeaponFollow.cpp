#include <systems/WeaponFollow.hpp>

#include <components/BoxCollider.hpp>
#include <components/CircleCollider.hpp>
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
    auto wielderView = entityManager_.view<components::WieldedWeapon, components::CircleCollider>();
    auto weaponView = entityManager_.view<components::Weapon, components::BoxCollider>();

    for (const auto& [wielder, wieldedWeapon, wielderCollider] : wielderView.each())
    {
        auto& weaponCollider = weaponView.get<components::BoxCollider>(wieldedWeapon.weaponEntity);

        weaponCollider.previousPosition = weaponCollider.position;
        weaponCollider.position = Vector2Add(wielderCollider.position, wieldedWeapon.colliderAttachOffset);
    }
}

} // spielda::system
