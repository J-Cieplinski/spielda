#ifndef SPIELDA_SPATIALGRID_HPP
#define SPIELDA_SPATIALGRID_HPP

#include <raymath.h>
#include <entt/entt.hpp>

#include <cstdint>
#include <list>
#include <optional>
#include <unordered_map>

namespace spielda
{

class SpatialGrid
{
using iterator = std::unordered_map<std::uint32_t, std::list<entt::entity>>::iterator;
using const_iterator = std::unordered_map<std::uint32_t, std::list<entt::entity>>::const_iterator;
public:
    SpatialGrid(std::uint32_t mapWidth, std::uint32_t mapHeight, std::uint32_t cellSize);

    std::vector<int> getNeighboringCells(const Vector2& position) const;
    std::optional<std::reference_wrapper<const std::list<entt::entity>>> at(std::uint32_t key) const;

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator cbegin() const;
    const_iterator end() const;
    const_iterator cend() const;
private:
    std::uint32_t mapWidth_;
    std::uint32_t mapHeight_;
    std::uint32_t cellSize_;
    std::unordered_map<std::uint32_t, std::list<entt::entity>> grid_;
};

} // namespace spielda


#endif