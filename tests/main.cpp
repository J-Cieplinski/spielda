#include <gtest/gtest.h>

TEST(TestyTest, ShouldFalse)
{
    ASSERT_FALSE(false);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}