#ifndef SPIELDA_GAME_GAME_HPP
#define SPIELDA_GAME_GAME_HPP

#include <roen/manager/GameSceneManager.hpp>

namespace spielda
{

class Game final
{
public:
    Game();
    void run();
private:
    roen::manager::GameSceneManager gameSceneManager_;
    bool isRunning_;
};

} // spielda

#endif //SPIELDA_GAME_GAME_HPP