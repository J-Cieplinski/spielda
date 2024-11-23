#include <systems/Mouse.hpp>

#include <CoreConfig.hpp>
#include <events/Mouse.hpp>

#include <raylib.h>
#include <raymath.h>

namespace spielda::system
{

Mouse::Mouse(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{eventDispatcher}
{
}

void Mouse::update()
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        eventDispatcher_.trigger(events::Mouse {
            .position = getVirtualMousePosition(),
            .mouseButton = MOUSE_BUTTON_LEFT
        });
    }
    else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        eventDispatcher_.trigger(events::Mouse {
            .position = getVirtualMousePosition(),
            .mouseButton = MOUSE_BUTTON_RIGHT
        });
    }
    else if(!Vector2Equals(GetMouseDelta(), Vector2Zero()))
    {
        eventDispatcher_.trigger(events::Mouse {
            .position = getVirtualMousePosition(),
            .mouseButton = -1
        });
    }
}

Vector2 Mouse::getVirtualMousePosition() const
{
    const float scale {std::min(static_cast<float>(GetScreenWidth())/RENDER_WIDTH, static_cast<float>(GetScreenHeight())/RENDER_HEIGHT)};

    const auto [mouseX, mouseY] = GetMousePosition();
    const Vector2 virtualMousePosition {
        .x = (mouseX - (static_cast<float>(GetScreenWidth()) - (RENDER_WIDTH * scale)) * 0.5f) / scale,
        .y = (mouseY - (static_cast<float>(GetScreenHeight()) - (RENDER_HEIGHT * scale)) * 0.5f) / scale,
    };

    return Vector2Clamp(virtualMousePosition, Vector2Zero(), Vector2{ RENDER_WIDTH, RENDER_HEIGHT });
}

} // spielda::system