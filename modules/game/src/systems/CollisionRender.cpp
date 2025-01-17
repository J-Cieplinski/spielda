#include <systems/CollisionRender.hpp>

#include <entt/entity/registry.hpp>

namespace spielda::system
{

CollisionRender::CollisionRender(entt::registry& entityManager, const Camera2D& camera)
    : IRenderSystem{entityManager, camera}
{
}

void CollisionRender::update()
{
    const auto entities = entityManager_.view<components::Collider>();
    BeginMode2D(camera_);

    entityManager_.view<components::Collider>().each([&](auto entity, const auto& collider) {
        std::visit([&](const auto& collider) {
            drawCollider(collider);
        }, collider);
    });

    EndMode2D();
}

void CollisionRender::drawCollider(const components::BoxCollider& collider)
{
    DrawRectangleLinesEx(collider, 0.8, collider.collisionType == CollisionType::WALL ? RED : GREEN);
}

void CollisionRender::drawCollider(const components::CircleCollider& collider)
{
    DrawCircleLinesV(collider.position, collider.radius, collider.collisionType == CollisionType::WALL ? RED : GREEN);
}

} // spielda::system