#include <systems/AIDetectRadiusRender.hpp>

#include <components/AI.hpp>
#include <components/Collider.hpp>
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
    //TODO: temporary move on variant Collider
    BeginMode2D(camera_);

    auto view = entityManager_.view<components::AI, components::Collider>();
    if (view.contains(detectedEntity_))
    {
        const auto ai = view.get<components::AI>(detectedEntity_);
        const auto collider = std::get<components::CircleCollider>(view.get<components::Collider>(detectedEntity_));

        DrawCircleLinesV(collider.position, ai.detectRadius, YELLOW);
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

    const auto aiView = entityManager_.view<components::AI, components::Transform, components::Collider>();
    const auto mousePosition = GetScreenToWorld2D(event.position, camera_);

    for (const auto& [entity, ai, transform, collider]: aiView.each())
    {
        auto circleCollider = std::get<components::CircleCollider>(collider);
        if (CheckCollisionPointCircle(mousePosition, circleCollider.position, circleCollider.radius))
        {
            detectedEntity_ = entity;
            return;
        }
    }
}

} // spielda::system