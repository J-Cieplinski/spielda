#ifndef SPIELDA_GAME_EVENTS_KEYBOARD_HPP
#define SPIELDA_GAME_EVENTS_KEYBOARD_HPP

#include <raylib.h>

namespace spielda::events
{

struct DebugSwitch
{
    bool switchRender;
    bool switchSdkLogging;
    bool switchAppLogging;
    bool switchCollisionSystem;
    //Rest of the variables for switching
};

} // spielda::events

#endif //SPIELDA_GAME_EVENTS_KEYBOARD_HPP
