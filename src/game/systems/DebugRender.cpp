#include <game/systems/DebugRender.hpp>

#include <game/components/Player.hpp>
#include <game/components/Transform.hpp>

#include <entt/entity/registry.hpp>

#include <raylib.h>

#include <sstream>

namespace spielda::system
{

DebugRender::DebugRender(entt::registry &entityManager)
    : ISystem{entityManager}
{
}

void DebugRender::update()
{
    std::stringstream ss;
    const auto player = entityManager_.group<components::Player>().front();
    const auto transform = entityManager_.try_get<components::Transform>(player);

    if(!transform)
    {
        return;
    }

    ss << "Player position\n" << "X: " << transform->position.x << "\t Y: " << transform->position.y;
    auto size = MeasureText(ss.str().c_str(), 15);
    Vector2 pos {
        .x = GetScreenWidth() - size - 5,
        .y = 20
    };

    DrawText(ss.str().c_str(), pos.x, pos.y, 15, RED);
}

} // namespace spielda::system
