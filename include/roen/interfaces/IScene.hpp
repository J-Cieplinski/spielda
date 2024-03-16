#ifndef ROEN_INTERFACES_ISCENE_HPP
#define ROEN_INTERFACES_ISCENE_HPP

#include <roen/container/SystemsContainer.hpp>

namespace roen::manager
{
class GameSceneManager;
} // roen::manager

namespace roen::interfaces
{

class IScene
{
public:
    explicit IScene(manager::GameSceneManager& gameSceneManager)
        : gameSceneManager_{gameSceneManager}
    {
    }

    virtual ~IScene() = default;

    virtual void handleInput() = 0;
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void obscured() = 0;
    virtual void revealed() = 0;

protected:
    manager::GameSceneManager& gameSceneManager_;
    container::SystemsContainer systems_;
};

} // roen::interfaces

#endif //ROEN_INTERFACES_ISCENE_HPP
