#ifndef SPIELDA_GAME_COMPONENTS_CHARACTERSHEET_HPP
#define SPIELDA_GAME_COMPONENTS_CHARACTERSHEET_HPP

#include <cstdint>

namespace spielda::components
{

struct CharacterSheet
{
    std::uint32_t intelligence;
    std::uint32_t strength;
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_CHARACTERSHEET_HPP
