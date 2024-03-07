#include <iostream>
#include <entt/entt.hpp>
#include <sol/sol.hpp>
#include <raylib.h>

int main()
{
    sol::state lua;
    std::string str {"razdwatrzy"};
    lua.set_function("print", [&str]{ std::cout << str << std::endl; });
    lua.script("print()");
    InitWindow(640, 480, str.c_str());

    entt::registry reg;
    auto ent = reg.create();
    std::cout << "Hello, World!" << std::endl;

    bool shouldClose {false};
    while(!shouldClose)
    {
        shouldClose = WindowShouldClose();
        BeginDrawing();
        EndDrawing();
    }

    return 0;
}
