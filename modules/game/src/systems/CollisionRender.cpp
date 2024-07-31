#include <systems/CollisionRender.hpp>

#include <components/BoxCollider.hpp>
#include <components/CircleCollider.hpp>

#include <entt/entity/registry.hpp>

namespace spielda::system
{

CollisionRender::CollisionRender(entt::registry& entityManager, const Camera2D& camera)
    : IRenderSystem{entityManager, camera}
{
}

void CollisionRender::update()
{
    const auto entities = entityManager_.view<components::BoxCollider>();
    const auto circleEntities = entityManager_.view<components::CircleCollider>();
    BeginMode2D(camera_);

    for(const auto& [_, boxCollider] : entities.each())
    {
        DrawRectangleLinesEx(boxCollider, 0.8, boxCollider.collisionType == CollisionType::WALL ? RED : GREEN);
    }

    for(const auto& [_, cirlceCollider] : circleEntities.each())
    {
        DrawCircleLinesV(cirlceCollider.position, cirlceCollider.radius, cirlceCollider.collisionType == CollisionType::WALL ? RED : GREEN);
    }

    EndMode2D();
}

} // spielda::system