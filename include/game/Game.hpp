#ifndef SPIELDA_GAME_GAME_HPP
#define SPIELDA_GAME_GAME_HPP

#include <roen/manager/GameSceneManager.hpp>

#include <cstdint>
#include <string>

namespace spielda
{

class Game final
{
public:
    Game(std::uint32_t windowWith = 1920, std::uint32_t windowHeight = 1080, const std::string& windowTitle = "Spielda");
    void run();
private:
    roen::manager::GameSceneManager gameSceneManager_;
    bool isRunning_;
};

} // spielda

#endif //SPIELDA_GAME_GAME_HPP