#ifndef SPIELDA_UTILS_HPP
#define SPIELDA_UTILS_HPP

#include <roen/include/Utils.hpp>
#include <roen/include/interfaces/IScene.hpp>
#include <roen/include/manager/GameSceneManager.hpp>

namespace spielda
{

template<typename NewScene>
requires std::is_base_of_v<roen::interfaces::IScene, NewScene>
class SwitchSceneFunctor : public roen::Functor
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

} // spielda

inline bool operator==(Vector2 lhs, Vector2 rhs)
{
    return std::tie(lhs.x, lhs.y) == std::tie(rhs.x, rhs.y);
}

#endif //SPIELDA_UTILS_HPP
