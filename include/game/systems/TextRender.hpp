#ifndef SPIELDA_GAME_SYSTEMS_TEXTRENDER_HPP
#define SPIELDA_GAME_SYSTEMS_TEXTRENDER_HPP

#include <roen/interfaces/ISystem.hpp>

#include <entt/entity/fwd.hpp>

#include <raylib.h>

namespace spielda::system
{

class TextRender final : public roen::interfaces::ISystem
{
public:
    explicit TextRender(entt::registry& entityManager);
    void update();
};

} // spielda::system


#endif //SPIELDA_GAME_SYSTEMS_TEXTRENDER_HPP