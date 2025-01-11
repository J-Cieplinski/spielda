#ifndef SPIELDA_GAME_SCENES_GAMESCENE_HPP
#define SPIELDA_GAME_SCENES_GAMESCENE_HPP

#include <roen/include/interfaces/IScene.hpp>

#include <events/DebugSwitch.hpp>

#include <entt/entity/registry.hpp>
#include <entt/signal/dispatcher.hpp>

#include <raylib.h>

#include <filesystem>
#include <json/single_include/nlohmann/json.hpp>

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
    void loadLevel(std::filesystem::path path);
    void loadHero(const nlohmann::json& level);
    void updateDeltaTime();
    void initSystems();
    void switchDebug(const events::DebugSwitch& event);
    void spawnDebugEntity();

    double deltaTime_;
    RenderTexture renderTexture_;
    Camera2D camera_;
    entt::registry entityManager_;
    entt::dispatcher eventDisptacher_;
    bool debugRender_;
    bool oldCollisionSystem_;
};

} // spielda::scenes

#endif //SPIELDA_GAME_SCENES_GAMESCENE_HPP