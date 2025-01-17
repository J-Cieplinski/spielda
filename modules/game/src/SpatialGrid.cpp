#include <SpatialGrid.hpp>

#include <components/Collider.hpp>

#include <roen/include/log/Logger.hpp>

namespace spielda
{

SpatialGrid::SpatialGrid(std::uint32_t mapWidth, std::uint32_t mapHeight, std::uint32_t cellSize)
    : mapWidth_{mapWidth}
    , mapHeight_{mapHeight}
    , cellSize_{cellSize}
{
}

void SpatialGrid::initGrid(const entt::registry& registry)
{
    registry.view<components::Collider>().each([this](entt::entity entity, const components::Collider& collider) 
    {
        std::visit([this, entity](const auto& col){
            updateEntityPosition(entity, Vector2{-1, -1}, col.position);
        }, collider);
    });
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

std::optional<std::reference_wrapper<std::list<entt::entity>>> SpatialGrid::at(std::uint32_t key)
{
    auto it = grid_.find(key);
    if(it != grid_.end())
    {
        return std::ref(it->second);
    }
    
    APP_WARN("No key {} present in SpatialGrid", key);
    
    return std::nullopt;
}


void SpatialGrid::updateEntityPosition(entt::entity entity, const Vector2 oldPosition, const Vector2 newPosition)
{
    auto oldCellIndex = getCellIndex(oldPosition);
    auto newCellIndex = getCellIndex(newPosition);

    if(oldCellIndex == newCellIndex)
    {
        return;
    }

    if(auto oldCell = at(oldCellIndex))
    {
        if(oldCell.has_value())
        {
            oldCell->get().remove(entity);
        }
    }

    grid_[newCellIndex].push_back(entity);
}

std::uint32_t SpatialGrid::getCellIndex(const Vector2& position) const
{
    auto cellX = static_cast<std::uint32_t>(position.x) / cellSize_;
    auto cellY = static_cast<std::uint32_t>(position.y) / cellSize_;
    return cellY * mapWidth_ + cellX;
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
