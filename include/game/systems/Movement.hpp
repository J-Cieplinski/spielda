#ifndef SPIELDA_GAME_SYSTEMS_MOVEMENT_HPP
#define SPIELDA_GAME_SYSTEMS_MOVEMENT_HPP

#include <roen/interfaces/ISystem.hpp>

namespace spielda::system
{

class Movement final : public roen::interfaces::ISystem
{
public:
    explicit Movement(entt::registry& entityManager);
    void update(double dt);
};

} // spielda::system



#endif //SPIELDA_GAME_SYSTEMS_MOVEMENT_HPP