#ifndef ROEN_DATA_STRUCTURE_MAPNODE_HPP
#define ROEN_DATA_STRUCTURE_MAPNODE_HPP

#include <data_structure/INode.hpp>

#include <cstdint>
#include <utility>

namespace roen::data_structure
{

class MapNode : public INode
{
public:
    MapNode(const std::pair<float, float>& position, const std::pair<std::uint32_t, std::uint32_t>& size, std::uint32_t cost);
    bool contains(const std::pair<float, float>& entity) const override;
    std::uint32_t cost() const override;
private:
    std::pair<float, float> position_;
    std::pair<std::uint32_t, std::uint32_t> size_;
    std::uint32_t movementCost_;
};

} // roen::data_structure

#endif //ROEN_DATA_STRUCTURE_MAPNODE_HPP