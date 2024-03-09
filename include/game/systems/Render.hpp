#ifndef SPIELDA_GAME_SYSTEMS_RENDER_HPP
#define SPIELDA_GAME_SYSTEMS_RENDER_HPP

#include <entt/entity/fwd.hpp>

#include <raylib.h>

namespace spielda::system
{

class Render
{
public:
    explicit Render(const entt::registry& entityManager, const Camera2D& camera);
    void update();
private:
    const entt::registry& entityManager_;
    const Camera2D& camera_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_RENDER_HPP