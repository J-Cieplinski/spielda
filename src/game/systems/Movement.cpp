#include <game/systems/Movement.hpp>

#include <game/components/BoxCollider.hpp>
#include <game/components/RigidBody.hpp>
#include <game/components/Transform.hpp>

#include <entt/entt.hpp>

namespace spielda::system
{

Movement::Movement(entt::registry &entityManager)
    : ISystem{entityManager}
{
}

void Movement::update(double dt)
{
    auto group = entityManager_.group<components::RigidBody>(entt::get<components::Transform, components::BoxCollider>);

    for(auto entity : group)
    {
        auto& transform = group.get<components::Transform>(entity);
        auto& collider = group.get<components::BoxCollider>(entity);
        auto rigidBody = group.get<components::RigidBody>(entity);

        transform.previousPosition = transform.position;
        collider.previousPosition = collider.position;

        transform.position.x += rigidBody.velocity.x * dt;
        transform.position.y += rigidBody.velocity.y * dt;
        collider.position.x += rigidBody.velocity.x * dt;
        collider.position.y += rigidBody.velocity.y * dt;
    }
}

} // spielda::system
