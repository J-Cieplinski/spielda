#ifndef SPIELDA_GAME_GAME_HPP
#define SPIELDA_GAME_GAME_HPP

#include <roen/include/Application.hpp>

#include <roen/EntryPoint.hpp>

#include <cstdint>
#include <string>

namespace spielda
{

class Game final : public roen::Application
{
public:
    Game(std::uint32_t windowWith = 1920, std::uint32_t windowHeight = 1080, const std::string& windowTitle = "Spielda");
    ~Game() override;

    void init() override;
};

} // spielda

inline std::unique_ptr<roen::Application> roen::createApplication()
{
    return std::make_unique<spielda::Game>(640, 480);
}

#endif //SPIELDA_GAME_GAME_HPP