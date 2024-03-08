#include <game/Game.hpp>

#include <game/scenes/GameScene.hpp>

#include <memory>

namespace spielda
{

Game::Game()
{
    currentScene_ = std::make_unique<GameScene>(*this);
}

void Game::run()
{
    currentScene_->handleInput();
    currentScene_->update();
    currentScene_->render();
}

void Game::changeScene(roen::SceneType scene)
{

}

} // spielda
