#ifndef SPIELDA_UTILS_HPP
#define SPIELDA_UTILS_HPP

#include <roen/include/Utils.hpp>
#include <roen/include/data_structure/Vector2.hpp>
#include <roen/include/interfaces/IScene.hpp>
#include <roen/include/manager/GameSceneManager.hpp>

#include <raylib.h>

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

inline Vector2 toRayVector(const roen::data_structure::Vector2f& v)
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

inline bool operator==(Vector2 lhs, Vector2 rhs)
{
    return std::tie(lhs.x, lhs.y) == std::tie(rhs.x, rhs.y);
}

#endif //SPIELDA_UTILS_HPP
