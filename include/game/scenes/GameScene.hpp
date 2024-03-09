#ifndef SPIELDA_GAME_SCENES_GAMESCENE_HPP
#define SPIELDA_GAME_SCENES_GAMESCENE_HPP

#include <roen/interfaces/IScene.hpp>

#include <memory>

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
};

} // spielda::scenes

#endif //SPIELDA_GAME_SCENES_GAMESCENE_HPP