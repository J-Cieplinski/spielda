#ifndef SPIELDA_GAME_SYSTEMS_KEYBOARD_HPP
#define SPIELDA_GAME_SYSTEMS_KEYBOARD_HPP

#include <roen/interfaces/ISystem.hpp>

namespace spielda::system
{

class Keyboard final : public roen::interfaces::ISystem
{
public:
    explicit Keyboard(entt::registry& entityManager);
    void update();
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_KEYBOARD_HPP