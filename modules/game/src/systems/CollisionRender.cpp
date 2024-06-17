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

    for(const auto& [_, boxCollider] : entities.each())
    {
        BeginMode2D(camera_);

        DrawRectangleLinesEx(boxCollider, 0.8, boxCollider.isColliding ? RED : GREEN);

        EndMode2D();
    }
}

} // spielda::system