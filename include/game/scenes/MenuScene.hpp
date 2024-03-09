#ifndef SPIELDA_GAME_SCENES_MENUSCENE_HPP
#define SPIELDA_GAME_SCENES_MENUSCENE_HPP

#include <roen/interfaces/IScene.hpp>

namespace spielda::scenes
{

class MenuScene final : public roen::interfaces::IScene
{
public:
    explicit MenuScene(roen::manager::GameSceneManager& gameSceneManager);

    void handleInput() override;
    void render() override;
    void update() override;
    void obscured() override;
    void revealed() override;
};

} // spielda::scenes

#endif //SPIELDA_GAME_SCENES_MENUSCENE_HPP