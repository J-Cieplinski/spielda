#include <game/MapLoader.hpp>

#include <game/Typedefs.hpp>
#include <game/components/BoxCollider.hpp>
#include <game/components/Sprite.hpp>
#include <game/components/Transform.hpp>

#include <raymath.h>

namespace spielda
{

MapLoader::MapLoader(entt::registry &entityManager)
    : BaseMapLoader(entityManager)
{
}

void MapLoader::addComponents(tson::Vector2f tilePosition, tson::Vector2i tileSize, float rotation, tson::Rect drawingRect,
                         int layerOrder, const std::string& layerClass, const std::string &assetId)
{
    static auto scale = Vector2(1.f, 1.f);

    auto tileEntity = entityManager_.create();
    auto position = Vector2(tilePosition.x, tilePosition.y);
    auto size = Vector2(tileSize.x, tileSize.y);
    auto rotationOffset = Vector2Scale(size, 0.5f);

    entityManager_.emplace<components::Transform>(tileEntity, Vector2Add(position, rotationOffset), scale, rotation);

    entityManager_.emplace<components::Sprite>(tileEntity,
                                                size,
                                                rotationOffset,
                                                Rectangle{static_cast<float>(drawingRect.x),
                                                            static_cast<float>(drawingRect.y),
                                                            static_cast<float>(drawingRect.width),
                                                            static_cast<float>(drawingRect.height)},
                                                static_cast<std::uint32_t>(layerOrder),
                                                static_cast<std::uint32_t>(layerOrder),
                                                roen::hashString(assetId),
                                                false);

    if(layerClass == roen::loader::LayerTypes::COLLIDABLE || layerClass == roen::loader::LayerTypes::TRIGGERS)
    {
        entityManager_.emplace<components::BoxCollider>(tileEntity, position, size, false);
    }
}

roen::manager::IAssetManager &MapLoader::getTextureManager()
{
    return entityManager_.ctx().get<TextureManager>();
}

} // spielda
