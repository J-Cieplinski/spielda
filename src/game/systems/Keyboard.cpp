#include <game/systems/Keyboard.hpp>

#include <game/components/Player.hpp>
#include <game/components/Sprite.hpp>
#include <game/components/Transform.hpp>

#include <roen/Utils.hpp>

#include <entt/entt.hpp>
#include <raylib.h>

namespace spielda::system
{

Keyboard::Keyboard(entt::registry &entityManager)
    : ISystem(entityManager)
{
}

void Keyboard::update()
{
    auto playerEntity = entityManager_.view<components::Player>().front();

    if(IsKeyReleased(KEY_D))
    {
        auto debugEnt = entityManager_.create();
        constexpr Rectangle srcRect {
                .x = 0.f,
                .y = 128.f,
                .width = 16.f,
                .height = 16.f
        };
        constexpr std::uint32_t layer = 5;
        constexpr std::uint32_t layerOrder = 1;
        constexpr Vector2 position {
                .x = 24,
                .y = 40
        };

        entityManager_.emplace<components::Sprite>(debugEnt, Vector2{16, 16}, Vector2{0, 0}, srcRect, layer, layerOrder, roen::hashString("dungeon"), false);
        entityManager_.emplace<components::Transform>(debugEnt, position, Vector2{1, 1}, 0.f);
    }
}

} // spielda::system