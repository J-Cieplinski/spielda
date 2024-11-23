#ifndef SPIELDA_UTILS_HPP
#define SPIELDA_UTILS_HPP

#include <roen/include/Utils.hpp>
#include <roen/include/interfaces/IScene.hpp>
#include <roen/include/manager/GameSceneManager.hpp>

#include <raymath.h>

namespace spielda
{

template<std::derived_from<roen::interfaces::IScene> NewScene>
class SwitchSceneFunctor final : public roen::Functor
{
public:
    explicit SwitchSceneFunctor(roen::manager::GameSceneManager& gameSceneManager)
        : gameSceneManager_{gameSceneManager}
    {
    }

    ~SwitchSceneFunctor() = default;

    void operator() () override
    {
        gameSceneManager_.switchScene(std::make_unique<NewScene>(gameSceneManager_));
    }
private:
    roen::manager::GameSceneManager& gameSceneManager_;
};

inline Vector2 toRayVector(const Vector2& v)
{
    return Vector2{v.x, v.y};
}

enum class CollisionType
{
    WEAPON,
    WALL,
    NONE
};

} // spielda

#endif //SPIELDA_UTILS_HPP
