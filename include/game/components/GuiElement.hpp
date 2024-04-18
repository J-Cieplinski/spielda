#ifndef SPIELDA_GAME_COMPONENTS_GUIELEMENT_HPP
#define SPIELDA_GAME_COMPONENTS_GUIELEMENT_HPP

#include <roen/Utils.hpp>

#include <memory>
#include <raylib.h>

namespace spielda::components
{

struct GuiElement
{
    NPatchInfo nPatchInfo;
    Vector2 size;
    Vector2 origin;
    std::uint64_t guid;
    std::uint64_t guidSelected;
    bool selected;
    std::unique_ptr<roen::Functor> callback;
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_GUIELEMENT_HPP
