#ifndef SPIELDA_GAME_SYSTEMS_GUIRENDER_HPP
#define SPIELDA_GAME_SYSTEMS_GUIRENDER_HPP

#include <roen/interfaces/ISystem.hpp>

#include <entt/entity/fwd.hpp>

#include <raylib.h>

namespace spielda::system
{

class GuiRender final : public roen::interfaces::ISystem
{
public:
    explicit GuiRender(entt::registry& entityManager);
    void update();
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_GUIRENDER_HPP