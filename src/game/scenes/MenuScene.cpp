#include <game/scenes/MenuScene.hpp>

#include <game/scenes/GameScene.hpp>

#include <roen/log/Logger.hpp>
#include <roen/manager/GameSceneManager.hpp>

namespace spielda::scenes
{

MenuScene::MenuScene(roen::manager::GameSceneManager &gameSceneManager)
    : IScene(gameSceneManager)
{

}

void MenuScene::handleInput()
{

}

void MenuScene::render()
{

}

void MenuScene::update()
{
    gameSceneManager_.push(std::make_unique<GameScene>(gameSceneManager_));
}

void MenuScene::obscured()
{

}

void MenuScene::revealed()
{
    APP_INFO("Entered MenuScene");
}

} // spielda::scenes
