#include <systems/Movement.hpp>

#include <components/BoxCollider.hpp>
#include <components/CircleCollider.hpp>
#include <components/RigidBody.hpp>
#include <components/Transform.hpp>

#include <entt/entt.hpp>

namespace spielda::system
{

Movement::Movement(entt::registry &entityManager)
    : ISystem{entityManager}
{
}

void Movement::update(double dt)
{
    auto group = entityManager_.group<components::RigidBody>(entt::get<components::Transform>);
    auto circleColliderView = entityManager_.view<components::CircleCollider>();
    auto boxColliderView = entityManager_.view<components::BoxCollider>();

    for(auto entity : group)
    {
        auto& transform = group.get<components::Transform>(entity);
        auto rigidBody = group.get<components::RigidBody>(entity);

        transform.previousPosition = transform.position;

        transform.position.x += rigidBody.velocity.x * dt;
        transform.position.y += rigidBody.velocity.y * dt;

        if(circleColliderView.contains(entity))
        {
            auto& collider = circleColliderView.get<components::CircleCollider>(entity);

            collider.previousPosition = collider.position;
            collider.position.x += rigidBody.velocity.x * dt;
            collider.position.y += rigidBody.velocity.y * dt;
        }
        else if(boxColliderView.contains(entity))
        {
            auto& collider = boxColliderView.get<components::BoxCollider>(entity);

            collider.previousPosition = collider.position;
            collider.position.x += rigidBody.velocity.x * dt;
            collider.position.y += rigidBody.velocity.y * dt;
        }
    }
}

} // spielda::system
