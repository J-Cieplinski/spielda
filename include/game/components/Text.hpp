#ifndef SPIELDA_GAME_COMPONENTS_TEXT_HPP
#define SPIELDA_GAME_COMPONENTS_TEXT_HPP

#include <raylib.h>
#include <string>

namespace spielda::components
{

struct Text
{
    std::string content;
    std::uint64_t font;
    float fontSize;
    Color color;
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_TEXT_HPP
