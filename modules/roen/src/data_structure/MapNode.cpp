#include <data_structure/MapNode.hpp>

namespace roen::data_structure
{

MapNode::MapNode(const std::pair<float, float>& position, const std::pair<std::uint32_t, std::uint32_t>& size,
                 std::uint32_t cost)
        : position_{position}
        , size_{size}
        , movementCost_{cost}
{
}

bool MapNode::contains(const std::pair<float, float>& entity) const
{
    return position_.first <= entity.first
        && (position_.first + size_.first) >= entity.first
        && position_.second <= entity.second
        && (position_.second + size_.second) >= entity.second;
}

std::uint32_t MapNode::cost() const
{
    return movementCost_;
}

} // roen::data_structure