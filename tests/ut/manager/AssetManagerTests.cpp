#include <roen/manager/AssetManager.hpp>

#include <roen/interfaces/IAsset.hpp>

#include <gtest/gtest.h>

namespace roen
{

namespace
{
const std::string FALSE_PATH {"FALSE"};
const std::string DUMMY_PATH {"DUMMY_PATH"};
const std::string DUMMY_ID {"DUMMY_ID"};
const std::string DUMMY_PATH_2 {"DUMMY_PATH_2"};
const std::string DUMMY_ID_2 {"DUMMY_ID_2"};
constexpr std::uint64_t DUMMY_HASH{123};

constexpr std::uint32_t VAL_FALSE{0};
constexpr std::uint32_t VAL_1{1};
constexpr std::uint32_t VAL_2{2};

const std::map<std::string, int> pathToVal = {
        {FALSE_PATH, VAL_FALSE},
        {DUMMY_PATH, VAL_1},
        {DUMMY_PATH_2, VAL_2}
};

}

namespace interfaces
{

template <int val>
class StubAsset : public Asset<int>
{
public:
    bool loadAsset(const std::string& path) override
    {
        asset_ = pathToVal.at(path);

        return asset_;
    }
    [[nodiscard]] int get() const override
    {
        return asset_;
    }
private:
    int asset_{val};
};

} // interfaces

namespace manager
{

class AssetManagerTests : public ::testing::TestWithParam<std::pair<bool, bool>>
{
};

TEST_F(AssetManagerTests, loadAsset_ShouldLoadAsset)
{
    auto sut = AssetManager<interfaces::StubAsset<VAL_1>>();
    EXPECT_NO_THROW(sut.loadAsset(DUMMY_ID, DUMMY_PATH));
    EXPECT_EQ(sut.getAsset(roen::hashString(DUMMY_ID)), VAL_1);
}

TEST_F(AssetManagerTests, loadAsset_ShouldThrowOnUnsucessfullAssetLoad)
{
    auto sut = AssetManager<interfaces::StubAsset<VAL_FALSE>>();
    EXPECT_THROW(sut.loadAsset(DUMMY_ID, FALSE_PATH), std::runtime_error);
}

TEST_F(AssetManagerTests, free_ShouldUnloadAssets)
{
    auto sut = AssetManager<interfaces::StubAsset<VAL_1>>();
    EXPECT_NO_THROW(sut.freeAssets());
    EXPECT_THROW(sut.getAsset(DUMMY_HASH), std::out_of_range);
}

TEST_F(AssetManagerTests, getAsset_ShouldThrowOnAccessingNotPresentAsset)
{
    auto sut = AssetManager<interfaces::StubAsset<VAL_1>>();
    EXPECT_THROW(sut.getAsset(DUMMY_HASH), std::out_of_range);
}

TEST_F(AssetManagerTests, getAsset_ShouldReturnCorrectAsset)
{
    auto sut = AssetManager<interfaces::StubAsset<VAL_1>>();
    EXPECT_NO_THROW(sut.loadAsset(DUMMY_ID, DUMMY_PATH));
    EXPECT_NO_THROW(sut.loadAsset(DUMMY_ID_2, DUMMY_PATH_2));
    EXPECT_EQ(sut.getAsset(roen::hashString(DUMMY_ID)), VAL_1);
    EXPECT_EQ(sut.getAsset(roen::hashString(DUMMY_ID_2)), VAL_2);
}

} // manager

} // roen