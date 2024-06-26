#ifndef ROEN_DATA_STRUCTURE_MAPNODE_HPP
#define ROEN_DATA_STRUCTURE_MAPNODE_HPP

#include <data_structure/INode.hpp>

#include <cstdint>
#include <unordered_map>
#include <utility>

namespace roen::data_structure
{

class MapNode : public INode
{
public:
    MapNode();
    MapNode(const std::pair<std::uint32_t, std::uint32_t>& position, const std::pair<std::uint32_t, std::uint32_t>& size, std::uint32_t cost);
    MapNode(const MapNode& other);
    friend bool operator==(const MapNode& lhs, const MapNode& rhs);
    friend bool operator<(const MapNode& lhs, const MapNode& rhs);
    std::pair<std::int32_t, std::int32_t> operator-(const MapNode& other) const;

    bool contains(const std::pair<float, float>& entity) const override;
    std::uint32_t cost() const override;
    const std::pair<std::uint32_t, std::uint32_t>& getPosition() const;
    const std::pair<std::uint32_t, std::uint32_t>& getSize() const;
private:
    friend std::hash<MapNode>;
    std::pair<std::uint32_t, std::uint32_t> position_;
    std::pair<std::uint32_t, std::uint32_t> size_;
    std::uint32_t movementCost_;
};

} // roen::data_structure

namespace std
{
    template <>
    struct hash<roen::data_structure::MapNode>
    {
        size_t operator()(const roen::data_structure::MapNode& node) const
        {
            return std::hash<std::uint32_t>()(node.position_.first ^ (node.position_.second << 16));
        }
    };
} // std

#endif //ROEN_DATA_STRUCTURE_MAPNODE_HPP