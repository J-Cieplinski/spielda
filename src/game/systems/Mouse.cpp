#include <game/systems/Mouse.hpp>

#include <game/events/Mouse.hpp>

#include <raylib.h>
#include <raymath.h>

namespace spielda::system
{

Mouse::Mouse(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem(entityManager)
    , eventDispatcher_(eventDispatcher)
{
}

void Mouse::update()
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        eventDispatcher_.trigger(events::Mouse {
            .position = GetMousePosition(),
            .mouseButton = MOUSE_BUTTON_LEFT
        });
    }
    else if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        eventDispatcher_.trigger(events::Mouse {
            .position = GetMousePosition(),
            .mouseButton = MOUSE_BUTTON_RIGHT
        });
    }
    else if(!Vector2Equals(GetMouseDelta(), Vector2Zero()))
    {
        eventDispatcher_.trigger(events::Mouse {
                .position = GetMousePosition(),
                .mouseButton = -1
        });
    }
}

} // spielda::system