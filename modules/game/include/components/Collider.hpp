#ifndef SPIELDA_GAME_COMPONENTS_COLLIDER_HPP
#define SPIELDA_GAME_COMPONENTS_COLLIDER_HPP

#include <components/BoxCollider.hpp>
#include <components/CircleCollider.hpp>

#include <variant>

namespace spielda::components
{

using Collider = std::variant<BoxCollider, CircleCollider>;

} // namespace spielda::components


#endif //SPIELDA_GAME_COMPONENTS_COLLIDER_HPP