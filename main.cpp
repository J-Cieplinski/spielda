#include <iostream>

#include <sol/sol.hpp>

#include <game/Game.hpp>
#include <roen/log/Logger.hpp>

int main()
{
    sol::state lua;
    std::string str {"Print from lua func"};
    lua.set_function("print", [&str]{ APP_INFO("{0}", str); });

    std::cout << "Hello, World!" << std::endl;
    spielda::Game game(640, 480);
    lua.script("print()");

    game.run();

    return 0;
}
