#include <MapLoader.hpp>

#include <Typedefs.hpp>
#include <Utilities.hpp>
#include <components/BoxCollider.hpp>
#include <components/Sprite.hpp>
#include <components/Transform.hpp>
#include <components/tags/CollisionMask.hpp>

#include <roen/include/Utils.hpp>

#include <raymath.h>

namespace spielda
{

MapLoader::MapLoader(entt::registry &entityManager)
    : BaseMapLoader{entityManager}
{
}

void MapLoader::addComponents(Vector2 tilePosition, Vector2 tileSize, float rotation, tson::Rect drawingRect,
                                int layerOrder, const std::string& layerClass, const std::string& assetId)
{
    constexpr auto scale = Vector2(1.f, 1.f);

    const auto tileEntity = entityManager_.create();
    const auto position = toRayVector(tilePosition);
    const auto size = toRayVector(tileSize);
    const auto origin = Vector2Scale(size, 0.5f);

    const auto renderedPosition = Vector2Add(position, origin);
    entityManager_.emplace<components::Transform>(tileEntity, renderedPosition, renderedPosition, scale, rotation);

    entityManager_.emplace<components::Sprite>(tileEntity,
                                                size,
                                                origin,
                                                Rectangle{static_cast<float>(drawingRect.x),
                                                            static_cast<float>(drawingRect.y),
                                                            static_cast<float>(drawingRect.width),
                                                            static_cast<float>(drawingRect.height)},
                                                static_cast<std::uint32_t>(layerOrder),
                                                static_cast<std::uint32_t>(layerOrder),
                                                roen::hashString(assetId),
                                                false);

    tags::CollisionMask collisionMask {
        .mask = tags::MaskLayer::DECORATION
    };

    if(layerClass == roen::loader::LayerTypes::COLLIDABLE || layerClass == roen::loader::LayerTypes::TRIGGERS)
    {
        entityManager_.emplace<components::BoxCollider>(tileEntity, position, position, size, CollisionType::NONE);
        collisionMask.mask |= tags::MaskLayer::WALL;
    }
    entityManager_.emplace<tags::CollisionMask>(tileEntity, collisionMask);
}

roen::manager::IAssetManager& MapLoader::getTextureManager()
{
    return entityManager_.ctx().get<TextureManager>();
}

} // spielda
