#include <roen/manager/GameSceneManager.hpp>

#include <roen/interfaces/IScene.hpp>

namespace roen::manager
{

void GameSceneManager::push(std::unique_ptr<interfaces::IScene> scene)
{
    if(!scenes_.empty())
    {
        scenes_.top()->obscured();
    }

    scene->revealed();
    scenes_.push(std::move(scene));
}

void GameSceneManager::pop()
{
    scenes_.pop();
    if(!scenes_.empty())
    {
        scenes_.top()->revealed();
    }
}

const std::unique_ptr<interfaces::IScene>& GameSceneManager::getCurrentScene()
{
    return scenes_.top();
}

} // roen::manager