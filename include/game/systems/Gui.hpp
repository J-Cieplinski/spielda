#ifndef SPIELDA_GAME_SYSTEMS_GUI_HPP
#define SPIELDA_GAME_SYSTEMS_GUI_HPP

#include <roen/interfaces/ISystem.hpp>

#include <game/events/Mouse.hpp>

#include <entt/entity/fwd.hpp>

#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

class Gui final : public roen::interfaces::ISystem
{
public:
    explicit Gui(entt::registry &entityManager, entt::dispatcher& eventDispatcher);
private:
    void onButtonHighlight(const events::Mouse& event);
    void onButtonPress(const events::Mouse& event);
    entt::dispatcher& eventDispatcher_;
};

}

#endif //SPIELDA_GAME_SYSTEMS_GUI_HPP