#include <systems/CollisionRender.hpp>

#include <components/BoxCollider.hpp>

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
    BeginMode2D(camera_);

    for(const auto& [_, boxCollider] : entities.each())
    {
        DrawRectangleLinesEx(boxCollider, 0.8, boxCollider.collisionType == components::CollisionType::WALL ? RED : GREEN);
    }

    EndMode2D();
}

} // spielda::system