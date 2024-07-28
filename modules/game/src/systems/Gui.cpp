#include <systems/Gui.hpp>

#include <components/BoxCollider.hpp>
#include <components/GuiElement.hpp>

#include <roen/include/log/Logger.hpp>

#include <raylib.h>

#include <entt/entt.hpp>

namespace spielda::system
{

Gui::Gui(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{eventDispatcher}
{
    eventDispatcher_.sink<events::Mouse>().connect<&Gui::onButtonHighlight>(this);
    eventDispatcher_.sink<events::Mouse>().connect<&Gui::onButtonPress>(this);
}

void Gui::onButtonHighlight(const events::Mouse& event)
{
    auto group = entityManager_.group<components::GuiElement>(entt::get<components::BoxCollider>);

    for(const auto entity : group)
    {
        const auto& collider = group.get<components::BoxCollider>(entity);
        auto& guiElement = group.get<components::GuiElement>(entity);

        auto mousePosition = event.position;
        guiElement.selected = CheckCollisionPointRec(mousePosition, collider);
    }
}

void Gui::onButtonPress(const events::Mouse& event)
{
    auto view = entityManager_.view<components::GuiElement>();

    for(const auto [entity, guiElement] : view.each())
    {
        if(!guiElement.selected)
        {
            continue;
        }

        switch(event.mouseButton)
        {
            case MOUSE_BUTTON_LEFT:
                if(guiElement.callback) (*guiElement.callback)();
                break;
            default:
                break;
        }
    }
}

} // spielda::system