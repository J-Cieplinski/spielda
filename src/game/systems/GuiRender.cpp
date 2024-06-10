#include <game/systems/GuiRender.hpp>

#include <game/Typedefs.hpp>

#include <game/components/GuiElement.hpp>
#include <game/components/Transform.hpp>

#include <entt/entt.hpp>

#include <raymath.h>

namespace spielda::system
{

GuiRender::GuiRender(entt::registry &entityManager)
    : ISystem{entityManager}
{
}

void GuiRender::update()
{
    auto entities = entityManager_.view<components::GuiElement, components::Transform>();

    const auto& textureManager = entityManager_.ctx().get<TextureManager>();

    for(const auto& [_, gui, transform] : entities.each())
    {
        const auto scaledSize  = Vector2Multiply(gui.size, transform.scale);

        const Rectangle dstRect {
            .x = transform.position.x,
            .y = transform.position.y,
            .width = scaledSize.x,
            .height = scaledSize.y
        };

        const auto& texture = gui.selected ? textureManager.getAsset(gui.guidSelected) : textureManager.getAsset(gui.guid);
        DrawTextureNPatch(texture, gui.nPatchInfo, dstRect, gui.origin, transform.rotation, WHITE);
    }
}

} // spielda::system