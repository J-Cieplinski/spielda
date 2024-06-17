#ifndef SPIELDA_GAME_SYSTEMS_DEBUGRENDER_HPP
#define SPIELDA_GAME_SYSTEMS_DEBUGRENDER_HPP

#include <systems/IRenderSystem.hpp>

#include <raylib.h>

namespace spielda::system
{

class DebugRender final : public IRenderSystem
{
public:
    explicit DebugRender(entt::registry& entityManager, const Camera2D& camera);
    void update() override;
};

} // spielda::system


#endif //SPIELDA_GAME_SYSTEMS_DEBUGRENDER_HPP