#ifndef SPIELDA_GAME_SYSTEMS_COLLISIONPARTITIONED_HPP
#define SPIELDA_GAME_SYSTEMS_COLLISIONPARTITIONED_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

class CollisionPartitioned final : public roen::interfaces::ISystem
{
public:
    explicit CollisionPartitioned(entt::registry& entityManager, entt::dispatcher& eventDispatcher);
    void update() const;
private:
    entt::dispatcher& eventDispatcher_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_COLLISIONPARTITIONED_HPP