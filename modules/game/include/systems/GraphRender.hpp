#ifndef SPIELDA_GAME_SYSTEMS_GRAPHRENDER_HPP
#define SPIELDA_GAME_SYSTEMS_GRAPHRENDER_HPP

#include <systems/IRenderSystem.hpp>

#include <roen/include/data_structure/Graph.hpp>
#include <roen/include/data_structure/MapNode.hpp>

#include <raylib.h>

namespace spielda::system
{

class GraphRender final : public IRenderSystem
{
public:
    explicit GraphRender(entt::registry& entityManager, const Camera2D& camera);
    void update() override;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_GRAPHRENDER_HPP