#ifndef ROEN_DATA_STRUCTURE_GRAPH_HPP
#define ROEN_DATA_STRUCTURE_GRAPH_HPP

#include <vector>
#include <unordered_map>

namespace roen::data_structure
{

template <typename Node>
class Graph
{
public:
    inline bool containsNode(const Node& node) const;
    inline const std::unordered_map<Node, std::vector<Node>>& getEdges() const;
    inline const std::vector<Node>& neighbors(const Node& node) const;
    void addNode(Node&& node, std::vector<Node>&& edges);
private:
    std::unordered_map<Node, std::vector<Node>> edges_;
};

/*
 * Template implementation
 */

template<typename Node>
inline bool Graph<Node>::containsNode(const Node& node) const
{
    return edges_.contains(node);
}

template<typename Node>
inline const std::unordered_map<Node, std::vector<Node>>& Graph<Node>::getEdges() const
{
    return edges_;
}

template<typename Node>
inline const std::vector<Node>& Graph<Node>::neighbors(const Node& node) const
{
    return edges_.at(node);
}

template<typename Node>
void Graph<Node>::addNode(Node&& node, std::vector<Node>&& edges)
{
    edges_[node] = edges;
}

} // roen::data_structure

#endif //ROEN_DATA_STRUCTURE_GRAPH_HPP