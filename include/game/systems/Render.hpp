#ifndef SPIELDA_GAME_SYSTEMS_RENDER_HPP
#define SPIELDA_GAME_SYSTEMS_RENDER_HPP

#include <roen/interfaces/ISystem.hpp>

#include <entt/entity/fwd.hpp>

#include <raylib.h>

namespace spielda::system
{

class Render final : public roen::interfaces::ISystem
{
public:
    explicit Render(const entt::registry& entityManager, const Camera2D& camera);
    void update() override;
private:
    const Camera2D& camera_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_RENDER_HPP