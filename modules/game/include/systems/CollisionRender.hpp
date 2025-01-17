#ifndef SPIELDA_GAME_SYSTEMS_COLLISIONRENDER_HPP
#define SPIELDA_GAME_SYSTEMS_COLLISIONRENDER_HPP

#include <systems/IRenderSystem.hpp>

#include <components/Collider.hpp>

#include <raylib.h>

namespace spielda::system
{

class CollisionRender final : public IRenderSystem
{
public:
    explicit CollisionRender(entt::registry& entityManager, const Camera2D& camera);
    void update() override;
private:
    void drawCollider(const components::BoxCollider& collider);
    void drawCollider(const components::CircleCollider& collider);
};

} // spielda::system


#endif //SPIELDA_GAME_SYSTEMS_COLLISIONRENDER_HPP