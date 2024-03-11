#include <roen/manager/GameSceneManager.hpp>

#include <roen/interfaces/IScene.hpp>

#include <stdexcept>

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
    if(scenes_.empty())
    {
        throw std::out_of_range("There are no game scenes present in the manager");
    }

    scenes_.pop();

    if(!scenes_.empty())
    {
        scenes_.top()->revealed();
    }
}

const std::unique_ptr<interfaces::IScene>& GameSceneManager::getCurrentScene()
{
    if(scenes_.empty())
    {
        throw std::out_of_range("There are no game scenes present in the manager");
    }

    return scenes_.top();
}

} // roen::manager