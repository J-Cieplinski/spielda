#ifndef SPIELDA_GAME_SYSTEMS_RENDER_HPP
#define SPIELDA_GAME_SYSTEMS_RENDER_HPP

#include <systems/IRenderSystem.hpp>

#include <components/Sprite.hpp>
#include <components/Transform.hpp>

#include <Typedefs.hpp>

#include <entt/entity/fwd.hpp>

#include <raylib.h>

namespace spielda::system
{

class Render final : public IRenderSystem
{
public:
    explicit Render(entt::registry& entityManager, const Camera2D& camera);
    void update() override;
private:
    void checkForDirtyAndSort();
    bool isComplex(entt::entity entity);
    void drawComplex(entt::entity entity, const components::Sprite& sprite, const components::Transform& transform, const spielda::TextureManager& textureManager);
    void drawAttached(entt::entity entity, const spielda::TextureManager& textureManager);
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_RENDER_HPP