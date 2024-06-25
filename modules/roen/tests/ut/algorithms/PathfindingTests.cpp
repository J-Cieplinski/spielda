#include <algorithms/search/Pathfinding.hpp>

#include <gtest/gtest.h>

namespace roen::algorithms
{

namespace
{

constexpr std::pair<std::uint32_t, std::uint32_t> DUMMY_SIZE {16, 16};
constexpr std::uint32_t DUMMY_COST {0};

} //

class PathfindingTests : public testing::Test
{
protected:
    const data_structure::MapNode startNode {{0,0}, DUMMY_SIZE, DUMMY_COST};
    const data_structure::MapNode middleNode{{16, 16}, DUMMY_SIZE, DUMMY_COST};
    const data_structure::MapNode endNode {{32,32}, DUMMY_SIZE, DUMMY_COST};
};

TEST_F(PathfindingTests, getNodeOrderFromPath_ShouldReturnCorrectPath)
{
    const std::unordered_map<data_structure::MapNode, data_structure::MapNode> path {
            {middleNode, startNode},
            {endNode, middleNode}
    };

    const std::vector<data_structure::MapNode> EXPECTED_ORDER {startNode, middleNode, endNode};

    EXPECT_EQ(getNodeOrderFromPath(startNode, endNode, path), EXPECTED_ORDER);
}

TEST_F(PathfindingTests, getNodeOrderFromPath_IfGoalDoesNotBelongToPathItShouldReturnEmptyVector)
{
    const std::unordered_map<data_structure::MapNode, data_structure::MapNode> path {
            {middleNode, startNode},
    };

    const std::vector<data_structure::MapNode> EXPECTED_ORDER {};

    EXPECT_EQ(getNodeOrderFromPath(startNode, endNode, path), EXPECTED_ORDER);
}

} // roen::algorithms
