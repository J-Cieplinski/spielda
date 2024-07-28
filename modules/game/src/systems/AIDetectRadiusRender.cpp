#include <systems/AIDetectRadiusRender.hpp>

#include <components/AI.hpp>
#include <components/BoxCollider.hpp>
#include <components/Transform.hpp>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include <raymath.h>

namespace spielda::system
{

AIDetectRadiusRender::AIDetectRadiusRender(entt::registry& entityManager, entt::dispatcher& dispatcher, const Camera2D &camera)
    : IRenderSystem{entityManager, camera}
    , eventDispatcher_{dispatcher}
    , detectedEntity_{entt::null}
{
    eventDispatcher_.sink<events::Mouse>().connect<&AIDetectRadiusRender::onMouseClick>(this);
}

void AIDetectRadiusRender::update()
{
    BeginMode2D(camera_);

    auto view = entityManager_.view<components::AI, components::BoxCollider>();
    if (view.contains(detectedEntity_))
    {
        const auto ai = view.get<components::AI>(detectedEntity_);
        const auto collider = view.get<components::BoxCollider>(detectedEntity_);
        const auto center = Vector2Add(collider.position, Vector2Scale(collider.size, 0.5f));

        DrawCircleLinesV(center, ai.detectRadius, YELLOW);
    }

    EndMode2D();
}

void AIDetectRadiusRender::onMouseClick(events::Mouse event)
{
    if (event.mouseButton != MOUSE_BUTTON_LEFT)
    {
        return;
    }

    detectedEntity_ = entt::null;

    const auto aiView = entityManager_.view<components::AI, components::Transform, components::BoxCollider>();

    for (const auto& [entity, ai, transform, collider]: aiView.each())
    {
        Rectangle boxCollider {
            .x = transform.position.x,
            .y = transform.position.y,
            .width = collider.size.x,
            .height = collider.size.y,
        };

        const auto mousePosition = GetScreenToWorld2D(event.position, camera_);

        if (CheckCollisionPointRec(mousePosition, boxCollider))
        {
            detectedEntity_ = entity;
            return;
        }
    }
}

} // spielda::system