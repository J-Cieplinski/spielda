#ifndef SPIELDA_GAME_SYSTEMS_DEBUGRENDER_HPP
#define SPIELDA_GAME_SYSTEMS_DEBUGRENDER_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <raylib.h>

namespace spielda::system
{

class DebugRender final : public roen::interfaces::ISystem
{
public:
    explicit DebugRender(entt::registry& entityManager, const Camera2D& camera);
    void update();
private:
    const Camera2D& camera_;
};

} // spielda::system


#endif //SPIELDA_GAME_SYSTEMS_DEBUGRENDER_HPP