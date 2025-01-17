#include <SpatialGrid.hpp>

#include <roen/include/log/Logger.hpp>

namespace spielda
{

SpatialGrid::SpatialGrid(std::uint32_t mapWidth, std::uint32_t mapHeight, std::uint32_t cellSize)
    : mapWidth_{mapWidth}
    , mapHeight_{mapHeight}
    , cellSize_{cellSize}
{

}


std::vector<int> SpatialGrid::getNeighboringCells(const Vector2& position) const
{
    std::vector<int> neighbors;
    int xCell = static_cast<int>(position.x) / cellSize_;
    int yCell = static_cast<int>(position.y) / cellSize_;

    for (int dx = -1; dx <= 1; ++dx)
    {
        for (int dy = -1; dy <= 1; ++dy)
        {
            int neighborX = xCell + dx;
            int neighborY = yCell + dy;

            if (neighborX >= 0 && neighborX < mapWidth_ && neighborY >= 0 && neighborY < mapHeight_)
            {
                auto neighborIndex = neighborY * mapWidth_ + neighborX;
                if(grid_.contains(neighborIndex))
                {
                    neighbors.push_back(neighborY * mapWidth_ + neighborX);
                }
            }
        }
    }

    return neighbors;
};

std::optional<std::reference_wrapper<const std::list<entt::entity>>> SpatialGrid::at(std::uint32_t key) const
{
    auto it = grid_.find(key);
    if(it != grid_.end())
    {
        return std::cref(it->second);
    }
    
    APP_WARN("No key {} present in SpatialGrid", key);
    
    return std::nullopt;
}

SpatialGrid::iterator SpatialGrid::begin()
{
    return grid_.begin();
}

SpatialGrid::iterator SpatialGrid::end()
{
    return grid_.end();
}

SpatialGrid::const_iterator SpatialGrid::begin() const
{
    return grid_.begin();
}

SpatialGrid::const_iterator SpatialGrid::cbegin() const
{
    return grid_.cbegin();
}

SpatialGrid::const_iterator SpatialGrid::end() const
{
    return grid_.end();
}

SpatialGrid::const_iterator SpatialGrid::cend() const
{
    return grid_.cend();
}

} // namespace spielda
