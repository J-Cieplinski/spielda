#ifndef SPIELDA_GAME_SYSTEMS_RENDER_HPP
#define SPIELDA_GAME_SYSTEMS_RENDER_HPP

#include <roen/interfaces/ISystem.hpp>

#include <game/components/Sprite.hpp>
#include <game/components/Transform.hpp>

#include <game/Typedefs.hpp>

#include <entt/entity/fwd.hpp>

#include <raylib.h>

namespace spielda::system
{

class Render final : public roen::interfaces::ISystem
{
public:
    explicit Render(entt::registry& entityManager, const Camera2D& camera);
    void update();
private:
    void checkForDirtyAndSort();
    bool isComplex(entt::entity entity);
    void drawComplex(entt::entity entity, const components::Sprite& sprite, const components::Transform& transform, const spielda::TextureManager& textureManager);
    void drawAttached(entt::entity entity, const spielda::TextureManager& textureManager);


    const Camera2D& camera_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_RENDER_HPP