#include <game/systems/WeaponFollow.hpp>

#include <game/components/BoxCollider.hpp>
#include <game/components/Transform.hpp>
#include <game/components/Weapon.hpp>

#include <entt/entt.hpp>
#include <raymath.h>

namespace spielda::system
{

WeaponFollow::WeaponFollow(entt::registry &entityManager)
    : ISystem(entityManager)
{
}

void WeaponFollow::update()
{
    auto group = entityManager_.group<components::Weapon>(entt::get<components::Transform, components::BoxCollider>);

    for(auto entity : group)
    {
        auto weapon = group.get<components::Weapon>(entity);
        auto owner = weapon.parentEntity;

        auto& weaponTransform = group.get<components::Transform>(entity);
        auto& weaponCollider = group.get<components::BoxCollider>(entity);
        const auto ownerTransform = group.get<components::Transform>(owner);

        weaponTransform.previousPosition = weaponTransform.position;
        weaponCollider.previousPosition = weaponTransform.position;
        weaponTransform.position = Vector2Add(weapon.relativePosition, ownerTransform.position);
        weaponCollider.position = weaponTransform.position;
    }
}

} // spielda::system
