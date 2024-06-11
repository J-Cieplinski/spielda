#ifndef SPIELDA_GAME_SYSTEMS_SPRITEDIRECTION_HPP
#define SPIELDA_GAME_SYSTEMS_SPRITEDIRECTION_HPP

#include <roen/include/interfaces/ISystem.hpp>

namespace spielda::system
{

class SpriteDirection final : public roen::interfaces::ISystem
{
public:
    explicit SpriteDirection(entt::registry& entityManager);
    void update();
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_SPRITEDIRECTION_HPP