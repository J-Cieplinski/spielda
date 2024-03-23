#include <game/systems/Movement.hpp>

#include <game/components/RigidBody.hpp>
#include <game/components/Transform.hpp>

#include <entt/entt.hpp>

namespace spielda::system
{

Movement::Movement(entt::registry &entityManager)
    : ISystem(entityManager)
{
}

void Movement::update(double dt)
{
    auto group = entityManager_.group<components::RigidBody>(entt::get<components::Transform>);

    for(auto entity : group)
    {
        auto& transform = group.get<components::Transform>(entity);
        auto rigidBody = group.get<components::RigidBody>(entity);

        transform.position.x += rigidBody.velocity.x * dt;
        transform.position.y += rigidBody.velocity.y * dt;
    }
}

} // spielda::system
