#include <systems/Movement.hpp>

#include <components/BoxCollider.hpp>
#include <components/CircleCollider.hpp>
#include <components/RigidBody.hpp>
#include <components/Sprite.hpp>
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
    auto group = entityManager_.group<components::RigidBody>(entt::get<components::Transform, components::Sprite>);
    auto circleColliderView = entityManager_.view<components::CircleCollider>();
    auto boxColliderView = entityManager_.view<components::BoxCollider>();

    for(auto entity : group)
    {
        auto rigidBody = group.get<components::RigidBody>(entity);

        if(rigidBody.velocity == Vector2Zero())
        {
            continue;
        }

        auto& sprite = group.get<components::Sprite>(entity);
        auto& transform = group.get<components::Transform>(entity);

        transform.previousPosition = transform.position;

        transform.position.x += rigidBody.velocity.x * dt;
        transform.position.y += rigidBody.velocity.y * dt;
        sprite.srcRect.width = abs(sprite.srcRect.width) * (rigidBody.lastVelocity.x != 0 ? rigidBody.lastVelocity.x : 1);

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
