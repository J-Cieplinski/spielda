#ifndef SPIELDA_GAME_SYSTEMS_ANIMATION_HPP
#define SPIELDA_GAME_SYSTEMS_ANIMATION_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

class Animation final : public roen::interfaces::ISystem
{
public:
    explicit Animation(entt::registry& entityManager);
    void update() const;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_ANIMATION_HPP