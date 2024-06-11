#ifndef SPIELDA_GAME_SCENES_MENUSCENE_HPP
#define SPIELDA_GAME_SCENES_MENUSCENE_HPP

#include <roen/include/interfaces/IScene.hpp>

#include <entt/entt.hpp>

#include <raylib.h>

namespace spielda::scenes
{

class MenuScene final : public roen::interfaces::IScene
{
public:
    explicit MenuScene(roen::manager::GameSceneManager& gameSceneManager);
    ~MenuScene();

    void handleInput() override;
    void render() override;
    void update() override;
    void obscured() override;
    void revealed() override;
    void quit() override;
private:
    void initAssets();
    void initSystems();
    void initEntities();
    void initBackground();
    void initButtons();

    entt::registry entityManager_;
    entt::dispatcher eventDisptacher_;
    RenderTexture renderTexture_;
    Camera2D camera_;
};

} // spielda::scenes

#endif //SPIELDA_GAME_SCENES_MENUSCENE_HPP