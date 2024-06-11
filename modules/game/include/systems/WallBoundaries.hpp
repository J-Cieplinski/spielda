#ifndef SPIELDA_GAME_SYSTEMS_BOUNDRIES_HPP
#define SPIELDA_GAME_SYSTEMS_BOUNDRIES_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <events/Collision.hpp>

#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

class WallBoundaries final : public roen::interfaces::ISystem
{
public:
    WallBoundaries(entt::registry& entityManager, entt::dispatcher& eventDispatcher);
private:
    void onCollision(const events::Collision& event);
    void rewindEntity(entt::entity entity);
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_BOUNDRIES_HPP