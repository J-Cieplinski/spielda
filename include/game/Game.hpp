#ifndef SPIELDA_GAME_GAME_HPP
#define SPIELDA_GAME_GAME_HPP

#include <roen/interfaces/IGame.hpp>

namespace spielda
{

class Game final : public roen::interfaces::IGame
{
public:
    Game();
    void run() override;
    void changeScene(roen::SceneType scene) override;
};

} // spielda

#endif //SPIELDA_GAME_GAME_HPP