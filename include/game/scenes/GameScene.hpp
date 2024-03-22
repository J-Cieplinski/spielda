#ifndef SPIELDA_GAME_SCENES_GAMESCENE_HPP
#define SPIELDA_GAME_SCENES_GAMESCENE_HPP

#include <roen/interfaces/IScene.hpp>

#include <entt/entity/registry.hpp>
#include <raylib.h>

namespace spielda::scenes
{

class GameScene final : public roen::interfaces::IScene
{
public:
    explicit GameScene(roen::manager::GameSceneManager& gameSceneManager);

    void handleInput() override;
    void render() override;
    void update() override;
    void obscured() override;
    void revealed() override;
private:
    void loadHero();

    RenderTexture renderTexture_;
    Camera2D camera_;
    entt::registry entityManager_;
};

} // spielda::scenes

#endif //SPIELDA_GAME_SCENES_GAMESCENE_HPP