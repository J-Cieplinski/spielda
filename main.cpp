#include <iostream>

#include <entt/entt.hpp>
#include <sol/sol.hpp>
#include <raylib.h>

#include <game/Game.hpp>
#include <roen/log/Logger.hpp>

int main()
{
    roen::log::Logger::Init();

    sol::state lua;
    std::string str {"razdwatrzy"};
    lua.set_function("print", [&str]{ APP_INFO("{0}", str); });
    lua.script("print()");
    InitWindow(640, 480, str.c_str());

    entt::registry reg;
    auto ent = reg.create();
    std::cout << "Hello, World!" << std::endl;
    spielda::Game game;
    game.run();

    bool shouldClose {false};
    while(!shouldClose)
    {
        shouldClose = WindowShouldClose();
        BeginDrawing();
        EndDrawing();
    }
    return 0;
}
