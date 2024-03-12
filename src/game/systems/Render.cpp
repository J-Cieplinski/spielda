#include <game/systems/Render.hpp>

#include <game/Typedefs.hpp>

#include <game/components/Sprite.hpp>
#include <game/components/Transform.hpp>

#include <entt/entity/registry.hpp>

namespace spielda::system
{

Render::Render(const entt::registry& entityManager, const Camera2D& camera)
    : ISystem{entityManager}
    , camera_{camera}
{
}

void Render::update()
{
    const auto entities = entityManager_.view<components::Sprite, components::Transform>();
    const auto& textureManager = entityManager_.ctx().get<TextureManager>();

    for(const auto& [_, sprite, transform] : entities.each())
    {
        Rectangle dstRect {
            .x = transform.position.x,
            .y = transform.position.y,
            .width = sprite.size.x * transform.scale.x,
            .height = sprite.size.y * transform.scale.y
        };

        if(!sprite.isFixed)
        {
            BeginMode2D(camera_);
        }

        DrawTexturePro(textureManager.getAsset(sprite.guid), sprite.srcRect, dstRect, {0, 0}, transform.rotation, WHITE);

        if(!sprite.isFixed)
        {
            EndMode2D();
        }
    }
}

} // spielda::system