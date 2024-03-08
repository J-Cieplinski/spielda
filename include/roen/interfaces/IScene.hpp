#ifndef ROEN_INTERFACES_ISCENE_HPP
#define ROEN_INTERFACES_ISCENE_HPP

namespace roen::interfaces
{

class IScene
{
public:
    ~IScene() = default;

    virtual void handleInput() = 0;
    virtual void render() = 0;
    virtual void update() = 0;
};

} // roen::interfaces

#endif //ROEN_INTERFACES_ISCENE_HPP
