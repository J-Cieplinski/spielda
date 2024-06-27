#include <systems/GraphRender.hpp>

#include <entt/entity/registry.hpp>

namespace spielda::system
{

namespace
{
using MapGraph = roen::data_structure::Graph<roen::data_structure::MapNode>;
} //

GraphRender::GraphRender(entt::registry& entityManager, const Camera2D& camera)
    : IRenderSystem{entityManager, camera}
{

}

void GraphRender::update()
{
    if(!entityManager_.ctx().contains<MapGraph>())
    {
        return;
    }

    const auto& pathfindingGraph = entityManager_.ctx().get<MapGraph>();
    for(const auto& [node, edges] : pathfindingGraph.getEdges())
    {
        BeginMode2D(camera_);

        const auto pos = node.getPosition();
        const auto size = node.getSize();
        Vector2 startPos {
            .x = static_cast<float>(pos.first + size.first / 2),
            .y = static_cast<float>(pos.second + size.second / 2)
        };

        for(const auto& edge : edges)
        {
            const auto edgePos = edge.getPosition();
            const auto edgeSize = edge.getSize();

            Vector2 endPos = {
                .x = static_cast<float>(edgePos.first + edgeSize.first / 2),
                .y = static_cast<float>(edgePos.second + edgeSize.second / 2)
            };

            DrawLineV(startPos, endPos, YELLOW);
        }

        DrawRectangleLines(pos.first, pos.second, size.first, size.second, MAGENTA);
        DrawCircle(startPos.x, startPos.y, 3.f, BLUE);

        EndMode2D();
    }
}

} // spielda::system