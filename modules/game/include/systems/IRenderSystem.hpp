#ifndef SPIELDA_GAME_SYSTEMS_IRENDERSYSTEM_HPP
#define SPIELDA_GAME_SYSTEMS_IRENDERSYSTEM_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <entt/entity/fwd.hpp>

#include <raylib.h>

namespace spielda::system
{
class IRenderSystem : public roen::interfaces::ISystem
{
public:
    explicit IRenderSystem(entt::registry& entityManager, const Camera2D& camera)
        : ISystem{entityManager}
        , camera_{camera}
    {

    }
    virtual void update() = 0;
protected:
    const Camera2D& camera_;
};
} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_IRENDERSYSTEM_HPP
