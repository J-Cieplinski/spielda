#include <Game.hpp>

#include <scenes/MenuScene.hpp>

#include <raylib.h>

namespace spielda
{

Game::Game(std::uint32_t windowWith, std::uint32_t windowHeight, const std::string& windowTitle)
    : isRunning_{true}
{
#ifdef IS_DEBUG
    roen::log::Logger::Init();
#endif

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowWith, windowHeight, windowTitle.c_str());

    gameSceneManager_.push(std::make_unique<scenes::MenuScene>(gameSceneManager_));
}

void Game::run()
{
    APP_INFO("Started main loop");

    while(isRunning_)
    {
        isRunning_ = !WindowShouldClose();
        gameSceneManager_.update();
        gameSceneManager_.getCurrentScene()->handleInput();
        gameSceneManager_.getCurrentScene()->update();
        gameSceneManager_.getCurrentScene()->render();
    }
}

} // spielda
