#ifndef SPIELDA_GAME_COMPONENTS_ANIMATION_HPP
#define SPIELDA_GAME_COMPONENTS_ANIMATION_HPP

#include <raylib.h>

#include <cstdint>

namespace spielda::components
{

enum class AnimationType
{
    HORIZONTAL,
    VERTICAL
};

struct Animation
{
    std::uint32_t numberOfFrames;
    std::uint32_t currentFrame;
    std::uint32_t frameRateSpeed;
    bool shouldLoop;
    double startTime;
    AnimationType type;

};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_ANIMATION_HPP
