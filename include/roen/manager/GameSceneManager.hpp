#ifndef ROEN_MANAGER_GAMESCENEMANAGER_HPP
#define ROEN_MANAGER_GAMESCENEMANAGER_HPP

#include <roen/interfaces/IScene.hpp>

#include <memory>
#include <stack>

namespace roen::manager
{

class GameSceneManager
{
public:
    void push(std::unique_ptr<interfaces::IScene> scene);
    void pop();
    const std::unique_ptr<interfaces::IScene>& getCurrentScene();
private:
    std::stack<std::unique_ptr<interfaces::IScene>> scenes_;
};

} // roen::manager

#endif //ROEN_MANAGER_GAMESCENEMANAGER_HPP