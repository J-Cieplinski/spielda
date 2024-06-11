#ifndef SPIELDA_GAME_SYSTEMS_DEBUGRENDER_HPP
#define SPIELDA_GAME_SYSTEMS_DEBUGRENDER_HPP

#include <roen/include/interfaces/ISystem.hpp>

namespace spielda::system
{

class DebugRender final : public roen::interfaces::ISystem
{
public:
    explicit DebugRender(entt::registry& entityManager);
    void update();
};

} // spielda::system


#endif //SPIELDA_GAME_SYSTEMS_DEBUGRENDER_HPP