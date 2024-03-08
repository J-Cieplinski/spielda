#ifndef SPIELDA_SCENES_GAMESCENE_HPP
#define SPIELDA_SCENES_GAMESCENE_HPP

#include <roen/interfaces/IScene.hpp>

namespace spielda
{

class GameScene final : public roen::interfaces::IScene
{
    void handleInput() override;
    void render() override;
    void update() override;
};

} // spielda

#endif //SPIELDA_SCENES_GAMESCENE_HPP