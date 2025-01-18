#include <systems/Render.hpp>

#include <components/AttachedEntities.hpp>
#include <components/Dirty.hpp>
#include <components/MapTile.hpp>
#include <components/Weapon.hpp>
#include <components/tags/Attachment.hpp>

#include <entt/entity/registry.hpp>

#include <raymath.h>
#include <rlgl.h>

namespace spielda::system
{

Render::Render(entt::registry& entityManager, const Camera2D& camera)
    : IRenderSystem{entityManager, camera}
    , mapPreRendered_{false}
{
}

void Render::preRenderMap(int width, int height)
{
    checkForDirtyAndSort();

    mapTexture_ = LoadRenderTexture(width, height);
    auto mapTiles = entityManager_.view<components::Sprite, components::Transform, components::MapTile>();
    mapTiles.use<components::Sprite>();
    const auto& textureManager = entityManager_.ctx().get<TextureManager>();

    BeginTextureMode(mapTexture_);
    ClearBackground(BLANK);

    for(const auto& [entity, sprite, transform] : mapTiles.each())
    {
        rlPushMatrix();
        rlTranslatef(transform.position.x, transform.position.y, 0); //move entity to its destined draw position
        rlScalef(transform.scale.x, transform.scale.y, 1);

        rlPushMatrix();
        rlRotatef(transform.rotation, 0, 0, 1); //rotate entity

        rlTranslatef(sprite.origin.x, sprite.origin.y, 0);

        DrawTextureRec(textureManager.getAsset(sprite.guid), sprite.srcRect, Vector2Zero(), WHITE);   //draw entity

        rlPopMatrix();

        rlPopMatrix();
    }

    EndTextureMode();

    mapPreRendered_ = true;
}


void Render::update()
{
    checkForDirtyAndSort();

    auto renderAbleEntities = entityManager_.view<components::Sprite, components::Transform>(entt::exclude<tags::Attachment, components::MapTile>);
    renderAbleEntities.use<components::Sprite>();
    const auto& textureManager = entityManager_.ctx().get<TextureManager>();
    const auto attachedEntitiesView = entityManager_.view<components::AttachedEntities>();

    BeginMode2D(camera_);

    if(mapPreRendered_)
    {
        DrawTextureRec(mapTexture_.texture,
            Rectangle{ 0.f, 0.f, static_cast<float>(mapTexture_.texture.width), -static_cast<float>(mapTexture_.texture.height) },
            Vector2{ 0, 0 },
            WHITE);
    }

    for(const auto& [entity, sprite, transform] : renderAbleEntities.each())
    {
        rlPushMatrix();
        rlTranslatef(transform.position.x, transform.position.y, 0); //move entity to its destined draw position
        rlScalef(transform.scale.x, transform.scale.y, 1);

        rlPushMatrix();
        rlRotatef(transform.rotation, 0, 0, 1); //rotate entity

        rlTranslatef(sprite.origin.x, sprite.origin.y, 0);

        DrawTextureRec(textureManager.getAsset(sprite.guid), sprite.srcRect, Vector2Zero(), WHITE);   //draw entity
        if(attachedEntitiesView.contains(entity))
        {
            for(const auto& attachedEntity : attachedEntitiesView.get<components::AttachedEntities>(entity).entities)
            {
                const auto& attachedSprite = renderAbleEntities.get<components::Sprite>(attachedEntity);
                const auto& attachedTransform = renderAbleEntities.get<components::Transform>(attachedEntity);

                rlPushMatrix();
                rlTranslatef(attachedTransform.position.x, attachedTransform.position.y, 0);
                rlScalef(attachedTransform.scale.x, attachedTransform.scale.y, 1);
                rlRotatef(attachedTransform.rotation, 0, 0, 1);
                rlTranslatef(attachedSprite.origin.x, attachedSprite.origin.y, 0);
                DrawTextureRec(textureManager.getAsset(attachedSprite.guid), attachedSprite.srcRect, Vector2Zero(), WHITE);   //draw attached entity
                rlPopMatrix();
            }
        }
        rlPopMatrix();

        rlPopMatrix();
    }

    EndMode2D();
}

void Render::checkForDirtyAndSort() const
{
    if(!entityManager_.view<components::Dirty>().empty())
    {
        APP_INFO("Detected dirty, sorting Sprites");

        entityManager_.sort<components::Sprite>([](const components::Sprite& lhs, const components::Sprite& rhs) {
            return lhs.layer < rhs.layer;
        });

        entityManager_.clear<components::Dirty>();
    }
}

} // spielda::system