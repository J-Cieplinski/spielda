#ifndef SPIELDA_GAME_SYSTEMS_COLLISIONRENDER_HPP
#define SPIELDA_GAME_SYSTEMS_COLLISIONRENDER_HPP

#include <roen/interfaces/ISystem.hpp>

#include <raylib.h>

namespace spielda::system
{

class CollisionRender final : public roen::interfaces::ISystem
{
public:
    explicit CollisionRender(const entt::registry& entityManager, const Camera2D& camera);
    void update() override;
private:
    const Camera2D& camera_;
};

} // spielda::system


#endif //SPIELDA_GAME_SYSTEMS_COLLISIONRENDER_HPP