#ifndef SPIELDA_GAME_SYSTEMS_COLLISION_HPP
#define SPIELDA_GAME_SYSTEMS_COLLISION_HPP

#include <roen/interfaces/ISystem.hpp>

namespace spielda::system
{

class Collision final : public roen::interfaces::ISystem
{
public:
    explicit Collision(entt::registry& entityManager);
    void update();
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_COLLISION_HPP