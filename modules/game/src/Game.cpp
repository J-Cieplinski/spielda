#include <Game.hpp>

#include <scenes/MenuScene.hpp>

#include <raylib.h>

namespace spielda
{

Game::Game(std::uint32_t windowWith, std::uint32_t windowHeight, const std::string& windowTitle)
    : Application{windowWith, windowHeight, windowTitle}
{
}

Game::~Game() = default;

void Game::init()
{
    gameSceneManager_.push(std::make_unique<scenes::MenuScene>(gameSceneManager_));
}

} // spielda
