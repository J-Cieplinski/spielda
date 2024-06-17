#include <systems/AIDetectRadiusRender.hpp>

#include <components/AI.hpp>
#include <components/BoxCollider.hpp>
#include <components/Transform.hpp>

#include <entt/entity/entity.hpp>
#include <entt/entity/registry.hpp>

#include <raymath.h>

namespace spielda::system
{

AIDetectRadiusRender::AIDetectRadiusRender(entt::registry& entityManager, entt::dispatcher& dispatcher, const Camera2D& camera)
    : ISystem{entityManager}
    , eventDispatcher_{dispatcher}
    , detectedEntity_{entt::null}
    , camera_{camera}
{
    eventDispatcher_.sink<events::Mouse>().connect<&AIDetectRadiusRender::onMouseClick>(this);
}

void AIDetectRadiusRender::update()
{
    if(const auto maybeAi = entityManager_.try_get<components::AI>(detectedEntity_))
    {
        const auto collider = entityManager_.get<components::BoxCollider>(detectedEntity_);
        const auto center = Vector2Add(collider.position, Vector2Scale(collider.size, 0.5f));

        BeginMode2D(camera_);

        DrawCircleLinesV(center, maybeAi->detectRadius, YELLOW);

        EndMode2D();
    }
}

void AIDetectRadiusRender::onMouseClick(events::Mouse event)
{
    const auto aiView = entityManager_.view<components::AI>();

    for(const auto ai : aiView)
    {
        const auto& transform = entityManager_.get<components::Transform>(ai);
        const auto& collider = entityManager_.get<components::BoxCollider>(ai);

        Rectangle boxCollider {
                .x = transform.position.x,
                .y = transform.position.y,
                .width = collider.size.x,
                .height = collider.size.y,
        };

        auto mousePosition = GetScreenToWorld2D(event.position, camera_);
        if(event.mouseButton == MOUSE_BUTTON_LEFT && CheckCollisionPointRec(mousePosition, boxCollider))
        {
            detectedEntity_ = ai;
            return;
        }
    }
}

} // spielda::system