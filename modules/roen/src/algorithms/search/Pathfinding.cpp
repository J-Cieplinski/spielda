#include <algorithms/search/Pathfinding.hpp>

#include <log/Logger.hpp>

namespace roen::algorithms
{

std::unordered_map<data_structure::MapNode, data_structure::MapNode> a_star(
        const data_structure::MapNode& start,
        const data_structure::MapNode& goal,
        const data_structure::Graph<data_structure::MapNode>& graph,
        const std::function<std::uint32_t(const data_structure::MapNode& nodeA, const data_structure::MapNode& nodeB)>& heuristic)
{
    return {};
}

std::vector<data_structure::MapNode> getNodeOrderFromPath(
        const data_structure::MapNode& start,
        const data_structure::MapNode& goal,
        const std::unordered_map<data_structure::MapNode, data_structure::MapNode>& path)
{
    std::vector<data_structure::MapNode> orderedPath {};
    auto current = goal;
    if(path.find(goal) == path.end())
    {
        SDK_WARN("Couldn't find path with goal: {0}", current.cost()); //TODO: print node coordinates
        return orderedPath;
    }

    while(current != start)
    {
        orderedPath.push_back(current);
        current = path.at(current);
    }

    orderedPath.push_back(start);
    std::reverse(orderedPath.begin(), orderedPath.end());

    return orderedPath;
}

} // roen::algorithms
