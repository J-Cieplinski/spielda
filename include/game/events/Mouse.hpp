#ifndef SPIELDA_GAME_EVENTS_MOUSE_HPP
#define SPIELDA_GAME_EVENTS_MOUSE_HPP

#include <raylib.h>

#include <cstdint>

namespace spielda::events
{

struct Mouse
{
    Vector2 position;
    std::int32_t mouseButton;
};

} // spielda::events

#endif //SPIELDA_GAME_EVENTS_MOUSE_HPP
