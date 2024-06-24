#ifndef ROEN_ALGORITHMS_SEARCH_PATHFINDING_HPP
#define ROEN_ALGORITHMS_SEARCH_PATHFINDING_HPP

#include <data_structure/MapNode.hpp>
#include <data_structure/Graph.hpp>

#include <vector>

namespace roen::algorithms
{

std::vector<data_structure::INode> a_star(const data_structure::MapNode& start,
                                          const data_structure::MapNode& goal,
                                          const data_structure::Graph<data_structure::MapNode>& graph);

} // roen::algorithms

#endif //ROEN_ALGORITHMS_SEARCH_PATHFINDING_HPP
