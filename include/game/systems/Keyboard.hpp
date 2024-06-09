#ifndef SPIELDA_GAME_SYSTEMS_KEYBOARD_HPP
#define SPIELDA_GAME_SYSTEMS_KEYBOARD_HPP

#include <roen/interfaces/ISystem.hpp>

#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

class Keyboard final : public roen::interfaces::ISystem
{
public:
    explicit Keyboard(entt::registry& entityManager, entt::dispatcher& eventDispatcher);
    void update();
private:
    void checkDebugInput();
    void checkPlayerInput();
    entt::dispatcher& eventDispatcher_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_KEYBOARD_HPP