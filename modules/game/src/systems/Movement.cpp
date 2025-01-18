#include <systems/Movement.hpp>

#include <SpatialGrid.hpp>

#include <components/Collider.hpp>
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
    auto colliderView = entityManager_.view<components::Collider>();
    auto& grid = entityManager_.ctx().get<SpatialGrid>();


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

        if(colliderView.contains(entity))
        {
            auto& collider = colliderView.get<components::Collider>(entity);
            std::visit([&](auto& col){
                col.previousPosition = col.position;
                col.position.x += rigidBody.velocity.x * dt;
                col.position.y += rigidBody.velocity.y * dt;

                grid.updateEntityPosition(entity, col.previousPosition, col.position);
            }, collider);
        }
    }
}

} // spielda::system
