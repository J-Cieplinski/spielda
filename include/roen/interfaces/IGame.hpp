#ifndef ROEN_INTERFACES_IGAME_HPP
#define ROEN_INTERFACES_IGAME_HPP

#include <roen/interfaces/IScene.hpp>
#include <roen/Utils.hpp>

#include <memory>

namespace roen::interfaces
{

class IGame
{
public:
    virtual ~IGame() = default;
    virtual void changeScene(SceneType scene) = 0;
    virtual void run() = 0;
protected:
    std::unique_ptr<IScene> currentScene_;
};

} // roen::interfaces

#endif //ROEN_INTERFACES_IGAME_HPP
