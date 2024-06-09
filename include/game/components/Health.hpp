#ifndef SPIELDA_GAME_COMPONENTS_HEALTH_HPP
#define SPIELDA_GAME_COMPONENTS_HEALTH_HPP

#include <cstdint>

namespace spielda::components
{

struct Health
{
    std::int32_t currentHealth;
    std::uint32_t maxHealth;
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_HEALTH_HPP
