#include <game/systems/Gui.hpp>

#include <game/components/BoxCollider.hpp>
#include <game/components/GuiElement.hpp>

#include <roen/log/Logger.hpp>

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
        const auto& collider = entityManager_.get<components::BoxCollider>(entity);
        auto& guiElement = entityManager_.get<components::GuiElement>(entity);

        Rectangle boxCollider {
            .x = collider.position.x,
            .y = collider.position.y,
            .width = collider.size.x,
            .height = collider.size.y,
        };

        auto mousePosition = event.position;
        guiElement.selected = CheckCollisionPointRec(mousePosition, boxCollider);
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