#include <game/systems/WeaponFollow.hpp>

#include <game/components/BoxCollider.hpp>
#include <game/components/Transform.hpp>
#include <game/components/Weapon.hpp>
#include <game/components/WieldedWeapon.hpp>

#include <entt/entt.hpp>
#include <raymath.h>

namespace spielda::system
{

WeaponFollow::WeaponFollow(entt::registry &entityManager)
    : ISystem{entityManager}
{
}

void WeaponFollow::update()
{
    auto view = entityManager_.view<components::WieldedWeapon>();
    auto weaponGroup = entityManager_.group<components::Weapon>(entt::get<components::BoxCollider>);

    for (auto weaponWielder : view)
    {
        auto wieldedWeapon = entityManager_.get<components::WieldedWeapon>(weaponWielder);
        auto& weaponCollider = weaponGroup.get<components::BoxCollider>(wieldedWeapon.weaponEntity);
        const auto ownerCollider = entityManager_.get<components::BoxCollider>(weaponWielder);

        weaponCollider.previousPosition = weaponCollider.position;
        weaponCollider.position = Vector2Add(ownerCollider.position, wieldedWeapon.colliderAttachOffset);
    }
}

} // spielda::system
