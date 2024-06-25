#include <data_structure/MapNode.hpp>

namespace roen::data_structure
{

MapNode::MapNode(const MapNode& other) = default;

MapNode::MapNode(const std::pair<std::uint32_t, std::uint32_t>& position, const std::pair<std::uint32_t, std::uint32_t>& size,
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

bool operator==(const MapNode& lhs, const MapNode& rhs)
{
    return lhs.position_ == rhs.position_
        && lhs.size_ == rhs.size_
        && lhs.movementCost_ == rhs.movementCost_;
}

} // roen::data_structure