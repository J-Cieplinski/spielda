#ifndef SPIELDA_GAME_SYSTEMS_MOUSE_HPP
#define SPIELDA_GAME_SYSTEMS_MOUSE_HPP

#include <entt/signal/dispatcher.hpp>
#include <roen/include/interfaces/ISystem.hpp>

namespace spielda::system
{

class Mouse final : public roen::interfaces::ISystem
{
public:
    explicit Mouse(entt::registry& entityManager, entt::dispatcher& eventDispatcher);
    void update();
private:
    entt::dispatcher& eventDispatcher_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_MOUSE_HPP