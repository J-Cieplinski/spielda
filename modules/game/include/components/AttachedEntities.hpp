#ifndef SPIELDA_GAME_COMPONENTS_ATTACHEDENTITIES_HPP
#define SPIELDA_GAME_COMPONENTS_ATTACHEDENTITIES_HPP

#include <entt/entity/entity.hpp>

namespace spielda::components
{

struct AttachedEntities
{
    std::set<entt::entity> entities;
};

} // spielda::components

#endif //SPIELDA_GAME_COMPONENTS_ATTACHEDENTITIES_HPP
