#include <data_structure/MapNode.hpp>

#include <gtest/gtest.h>

namespace roen::data_structure
{

class MapNodeTests : public testing::Test
{
};

TEST_F(MapNodeTests, cost_ShouldReturnCorrectNodeCost)
{
    constexpr std::uint32_t NODE_COST {1};
    MapNode node({0, 0}, {16, 16}, NODE_COST);

    EXPECT_EQ(node.cost(), NODE_COST);
}

TEST_F(MapNodeTests, contains_ShouldReturnTrueIfEntityIsWithinNode)
{
    constexpr std::uint32_t NODE_COST {1};
    MapNode node({0, 0}, {16, 16}, NODE_COST);

    constexpr std::pair<float, float> CONTAINED_ENTITY {14.5f, 0.f};

    EXPECT_TRUE(node.contains(CONTAINED_ENTITY));
}

TEST_F(MapNodeTests, contains_ShouldReturnFalseIfEntityIsNotWithinNode)
{
    constexpr std::uint32_t NODE_COST {1};
    MapNode node({0, 0}, {16, 16}, NODE_COST);

    constexpr std::pair<float, float> NOT_CONTAINED_ENTITY {16.5f, 0.f};

    EXPECT_FALSE(node.contains(NOT_CONTAINED_ENTITY));
}

} // roen::data_structure