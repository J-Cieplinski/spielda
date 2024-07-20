#ifndef SPIELDA_GAME_SCENES_GAMESCENE_HPP
#define SPIELDA_GAME_SCENES_GAMESCENE_HPP

#include <roen/include/interfaces/IScene.hpp>

#include <events/DebugSwitch.hpp>

#include <roen/include/data_structure/Graph.hpp>
#include <roen/include/data_structure/MapNode.hpp>

#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>
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
    void quit() override;
private:
    void loadHero();
    void updateDeltaTime();
    void initSystems();
    void switchDebug(const events::DebugSwitch& event);

    double deltaTime_;
    RenderTexture renderTexture_;
    Camera2D camera_;
    entt::registry entityManager_;
    entt::dispatcher eventDisptacher_;
    bool debugRender_;
};

} // spielda::scenes

#endif //SPIELDA_GAME_SCENES_GAMESCENE_HPP