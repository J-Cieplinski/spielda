#include <game/Game.hpp>

#include <game/scenes/MenuScene.hpp>

namespace spielda
{

Game::Game()
    : isRunning_{true}
{
    gameSceneManager_.push(std::make_unique<scenes::MenuScene>(gameSceneManager_));
}

void Game::run()
{
    while(isRunning_)
    {
        gameSceneManager_.getCurrentScene()->handleInput();
        gameSceneManager_.getCurrentScene()->update();
        gameSceneManager_.getCurrentScene()->render();
    }
}

} // spielda
