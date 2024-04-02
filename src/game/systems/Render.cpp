#include <game/systems/Render.hpp>

#include <game/Typedefs.hpp>

#include <game/components/Dirty.hpp>
#include <game/components/Sprite.hpp>
#include <game/components/Transform.hpp>

#include <entt/entity/registry.hpp>

#include <raymath.h>

namespace spielda::system
{

Render::Render(entt::registry& entityManager, const Camera2D& camera)
    : ISystem{entityManager}
    , camera_{camera}
{
}

void Render::update()
{
    checkForDirtyAndSort();

    auto entities = entityManager_.view<components::Sprite, components::Transform>();
    entities.use<components::Sprite>();

    const auto& textureManager = entityManager_.ctx().get<TextureManager>();

    for(const auto& [_, sprite, transform] : entities.each())
    {
        const auto scaledSize  = Vector2Multiply(sprite.size, transform.scale);

        const Rectangle dstRect {
            .x = transform.position.x,
            .y = transform.position.y,
            .width = scaledSize.x,
            .height = scaledSize.y
        };

        if(!sprite.isFixed)
        {
            BeginMode2D(camera_);
        }

        DrawTexturePro(textureManager.getAsset(sprite.guid), sprite.srcRect, dstRect, sprite.origin, transform.rotation, WHITE);

        if(!sprite.isFixed)
        {
            EndMode2D();
        }
    }
}

void Render::checkForDirtyAndSort()
{
    if(!entityManager_.view<components::Dirty>().empty())
    {
        entityManager_.sort<components::Sprite>([](const components::Sprite& lhs, const components::Sprite& rhs) {
            return lhs.layer < rhs.layer;
        });

        entityManager_.clear<components::Dirty>();
    }
}

} // spielda::system