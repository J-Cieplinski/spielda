#ifndef ROEN_INTERFACES_ISCENE_HPP
#define ROEN_INTERFACES_ISCENE_HPP

namespace roen::interfaces
{

class IGame;

class IScene
{
public:
    explicit IScene(IGame& game)
        : game_{game}
    {
    }

    virtual ~IScene() = default;

    virtual void handleInput() = 0;
    virtual void render() = 0;
    virtual void update() = 0;
protected:
    IGame& game_;
};

} // roen::interfaces

#endif //ROEN_INTERFACES_ISCENE_HPP
