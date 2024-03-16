#include <game/systems/CollisionRender.hpp>

#include <game/components/BoxCollider.hpp>

#include <entt/entity/registry.hpp>

namespace spielda::system
{

CollisionRender::CollisionRender(const entt::registry& entityManager, const Camera2D& camera)
        : ISystem{entityManager}
        , camera_{camera}
{
}

void CollisionRender::update()
{
    const auto entities = entityManager_.view<components::BoxCollider>();

    for(const auto& [_, boxCollider] : entities.each())
    {
        Rectangle collisionBox = {
                .x = boxCollider.position.x,
                .y = boxCollider.position.y,
                .width = boxCollider.size.x,
                .height = boxCollider.size.y
        };

        BeginMode2D(camera_);

        DrawRectangleLinesEx(collisionBox, 0.8, boxCollider.isColliding ? RED : GREEN);

        EndMode2D();
    }
}

} // spielda::system