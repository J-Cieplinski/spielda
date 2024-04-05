#include <game/systems/TextRender.hpp>

#include <game/components/Text.hpp>
#include <game/components/Transform.hpp>

#include <game/Typedefs.hpp>

#include <entt/entt.hpp>
#include <raylib.h>
#include <raymath.h>

namespace spielda::system
{

TextRender::TextRender(entt::registry &entityManager)
    : ISystem(entityManager)
{

}

void TextRender::update()
{
    auto group = entityManager_.group<components::Text>(entt::get<components::Transform>);
    auto& fontManager = entityManager_.ctx().get<spielda::FontManager>();

    for(const auto& entity : group)
    {
        const auto& transform = group.get<components::Transform>(entity);
        const auto& text = group.get<components::Text>(entity);
        auto font = fontManager.getAsset(text.font);

        const auto stringSize = MeasureTextEx(font, text.content.c_str(), text.fontSize, 0);
        const auto origin = Vector2Scale(stringSize, 0.5f);

        DrawTextPro(font, text.content.c_str(), transform.position, origin, 0.f, text.fontSize, 0, text.color);
    }

}

} // spielda::system