#include <game/scenes/GameScene.hpp>

#include <game/systems/Render.hpp>

#include <roen/log/Logger.hpp>
#include <roen/manager/GameSceneManager.hpp>

namespace spielda::scenes
{

GameScene::GameScene(roen::manager::GameSceneManager& gameSceneManager)
    : IScene(gameSceneManager)
{
}

void GameScene::handleInput()
{

}

void GameScene::render()
{

}

void GameScene::update()
{

}

void GameScene::obscured()
{

}

void GameScene::revealed()
{
    APP_INFO("Entered GameScene");
}

} // spielda::scenes