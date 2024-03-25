#ifndef SPIELDA_GAME_SYSTEMS_KEYBOARD_HPP
#define SPIELDA_GAME_SYSTEMS_KEYBOARD_HPP

#include <entt/signal/dispatcher.hpp>
#include <roen/interfaces/ISystem.hpp>

namespace spielda::system
{

class Keyboard final : public roen::interfaces::ISystem
{
public:
    explicit Keyboard(entt::registry& entityManager, entt::dispatcher& eventDispatcher);
    void update();
private:
    entt::dispatcher& eventDispatcher_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_KEYBOARD_HPP