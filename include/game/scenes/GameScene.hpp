#ifndef SPIELDA_GAME_SCENES_GAMESCENE_HPP
#define SPIELDA_GAME_SCENES_GAMESCENE_HPP

#include <game/Game.hpp>

#include <roen/interfaces/IScene.hpp>

#include <memory>

namespace spielda
{

class GameScene final : public roen::interfaces::IScene
{
public:
    GameScene(Game& game);

    void handleInput() override;
    void render() override;
    void update() override;
};

} // spielda

#endif //SPIELDA_GAME_SCENES_GAMESCENE_HPP