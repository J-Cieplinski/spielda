#include <data_structure/MapNode.hpp>

namespace roen::data_structure
{

MapNode::MapNode() = default;

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

std::pair<std::int32_t, std::int32_t> MapNode::operator-(const MapNode &other) const
{
    return {(position_.first - other.position_.first), (position_.second - other.position_.second)};
}

bool operator<(const MapNode& lhs, const MapNode& rhs)
{
    return std::tie(lhs.position_.first, lhs.position_.second) < std::tie(rhs.position_.first, rhs.position_.second);
}

} // roen::data_structure