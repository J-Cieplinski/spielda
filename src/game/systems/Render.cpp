#include <game/systems/Render.hpp>

#include <game/components/Dirty.hpp>
#include <game/components/Weapon.hpp>
#include <game/components/WieldedWeapon.hpp>

#include <entt/entity/registry.hpp>

#include <raymath.h>
#include <rlgl.h>

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

    for(const auto& [entity, sprite, transform] : entities.each())
    {

        if(!sprite.isFixed)
        {
            BeginMode2D(camera_);
        }

        if(!isComplex(entity))
        {
            const auto scaledSize  = Vector2Multiply(sprite.size, transform.scale);

            const Rectangle dstRect {
                .x = transform.position.x,
                .y = transform.position.y,
                .width = scaledSize.x,
                .height = scaledSize.y
            };

            DrawTexturePro(textureManager.getAsset(sprite.guid), sprite.srcRect, dstRect, sprite.origin, transform.rotation, WHITE);
        }
        else
        {
            drawComplex(entity, sprite, transform, textureManager);
        }

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
        APP_INFO("Detected dirty, sorting Sprites");

        entityManager_.sort<components::Sprite>([](const components::Sprite& lhs, const components::Sprite& rhs) {
            return lhs.layer < rhs.layer;
        });

        entityManager_.clear<components::Dirty>();
    }
}

bool Render::isComplex(entt::entity entity)
{
    bool hasWeapon = entityManager_.any_of<components::WieldedWeapon>(entity);
    bool isWeapon = entityManager_.any_of<components::Weapon>(entity);
    
    return hasWeapon || isWeapon;
}

void Render::drawComplex(entt::entity entity, const components::Sprite& sprite, const components::Transform& transform, const spielda::TextureManager& textureManager)
{
    auto weaponComp = entityManager_.try_get<components::Weapon>(entity);
    if(weaponComp)
    {
        return;
    }

    const auto wieldedWeapon = entityManager_.get<components::WieldedWeapon>(entity);

    const auto scaledSize  = Vector2Multiply(sprite.size, transform.scale);

    const Rectangle dstRect {
        .x = transform.position.x,
        .y = transform.position.y,
        .width = scaledSize.x,
        .height = scaledSize.y
    };

    DrawTexturePro(textureManager.getAsset(sprite.guid), sprite.srcRect, dstRect, sprite.origin, transform.rotation, WHITE);

    rlPushMatrix();

    const auto weaponPositionOnEntity = Vector2Add(transform.position, wieldedWeapon.weaponAttachOffset);
    rlTranslatef(weaponPositionOnEntity.x, weaponPositionOnEntity.y, 0);

    //Draw the weapon here
    drawAttached(wieldedWeapon.weaponEntity, textureManager);

    rlPopMatrix();
}

void Render::drawAttached(entt::entity entity, const spielda::TextureManager& textureManager)
{
    const auto transform = entityManager_.get<components::Transform>(entity);
    rlRotatef(transform.rotation, 0, 0, 1);

    rlPushMatrix();
    const auto weapon = entityManager_.get<components::Weapon>(entity);

    float yOrigin = weapon.originPosition.y;

    rlTranslatef(-weapon.originPosition.x, -yOrigin, 0);

    const auto sprite = entityManager_.get<components::Sprite>(entity);

    const auto scaledSize  = Vector2Multiply(sprite.size, transform.scale);

    DrawTextureRec(textureManager.getAsset(sprite.guid), sprite.srcRect, Vector2Zero(), WHITE);

    rlPopMatrix();
}

} // spielda::system