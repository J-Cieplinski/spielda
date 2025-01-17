#ifndef SPIELDA_GAME_SYSTEMS_COLLISIONPARTITIONED_HPP
#define SPIELDA_GAME_SYSTEMS_COLLISIONPARTITIONED_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <components/Collider.hpp>

#include <raymath.h>
#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

class CollisionPartitioned final : public roen::interfaces::ISystem
{
public:
    explicit CollisionPartitioned(entt::registry& entityManager, entt::dispatcher& eventDispatcher);
    void update() const;
private:
    Vector2 getColliderPosition(const components::Collider& collider) const;
    bool checkCollision(const components::Collider& colliderA, const components::Collider& colliderB) const;
    bool checkCircleBoxCollision(const components::Collider& colliderA, const components::Collider& colliderB) const;

    entt::dispatcher& eventDispatcher_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_COLLISIONPARTITIONED_HPP