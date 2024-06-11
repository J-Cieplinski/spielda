#ifndef SPIELDA_GAME_SYSTEMS_COLLISION_HPP
#define SPIELDA_GAME_SYSTEMS_COLLISION_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

class Collision final : public roen::interfaces::ISystem
{
public:
    explicit Collision(entt::registry& entityManager, entt::dispatcher& eventDispatcher);
    void update();
private:
    entt::dispatcher& eventDispatcher_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_COLLISION_HPP