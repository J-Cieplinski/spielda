#ifndef ROEN_INTERFACES_ISCENE_HPP
#define ROEN_INTERFACES_ISCENE_HPP

namespace roen::manager
{
class GameSceneManager;
} // roen::manager

namespace roen::interfaces
{

class IGame;

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
};

} // roen::interfaces

#endif //ROEN_INTERFACES_ISCENE_HPP