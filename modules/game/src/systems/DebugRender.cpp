#include <systems/DebugRender.hpp>

#include <components/AI.hpp>
#include <components/Collider.hpp>
#include <components/Player.hpp>
#include <components/RigidBody.hpp>
#include <components/Transform.hpp>

#include <entt/entity/registry.hpp>

#include <raylib.h>
#include <raymath.h>

#include <sstream>

namespace spielda::system
{

DebugRender::DebugRender(entt::registry &entityManager, const Camera2D& camera)
    : IRenderSystem{entityManager, camera}
{
}

void DebugRender::update()
{
    //TODO: temporary measures for Collider
    std::stringstream ss;
    const auto player = entityManager_.group<components::Player>().front();
    const auto transform = entityManager_.try_get<components::Transform>(player);
    const auto collider = std::get<components::CircleCollider>(entityManager_.get<components::Collider>(player));

    if(!transform)
    {
        return;
    }

    auto mousePos = GetScreenToWorld2D(GetMousePosition(), camera_);

    ss << "Player position\n" << "X: " << transform->position.x << "\t Y: " << transform->position.y;
    ss << "\nPlayer collider position\n" << "X: " << collider.position.x << "\t Y: " << collider.position.y;
    ss << "\nMouse position\n" << "X: " << mousePos.x << "\t Y: " << mousePos.y;

    auto size = MeasureText(ss.str().c_str(), 15);
    Vector2 pos {
        .x = static_cast<float>(GetScreenWidth() - size - 5),
        .y = 20
    };

    DrawText(ss.str().c_str(), pos.x, pos.y, 15, RED);
}

} // namespace spielda::system
