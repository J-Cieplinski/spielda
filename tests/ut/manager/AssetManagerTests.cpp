#include <roen/manager/AssetManager.hpp>

#include <roen/interfaces/IAsset.hpp>

#include <gtest/gtest.h>

namespace roen
{

namespace interfaces
{

template <bool val>
class StubAsset : public Asset<bool>
{
public:
    bool loadAsset(const std::string& path) override
    {
        return val;
    }
    [[nodiscard]] bool get() const override
    {
        return asset_;
    }
private:
    bool asset_{val};
};

} // interfaces

namespace manager
{

namespace
{
const std::string DUMMY_PATH {"DUMMY_PATH"};
const std::string DUMMY_ID {"DUMMY_ID"};
constexpr std::uint64_t DUMMY_HASH{123};
}

class AssetManagerTests : public ::testing::TestWithParam<std::pair<bool, bool>>
{
};

TEST_F(AssetManagerTests, ShouldThrowOnUnsucessfullAssetLoad)
{
    auto sut = AssetManager<interfaces::StubAsset<false>>();
    EXPECT_THROW(sut.loadAsset(DUMMY_ID, DUMMY_PATH), std::runtime_error);
}

TEST_F(AssetManagerTests, FreeShouldUnloadAssets)
{
    auto sut = AssetManager<interfaces::StubAsset<true>>();
    EXPECT_NO_THROW(sut.loadAsset(DUMMY_ID, DUMMY_PATH));
    EXPECT_TRUE(sut.getAsset(roen::hashString(DUMMY_ID)));
}

TEST_F(AssetManagerTests, ShouldThrowOnAccessingUnloadedAsset)
{
    auto sut = AssetManager<interfaces::StubAsset<true>>();
    EXPECT_THROW(sut.getAsset(DUMMY_HASH), std::out_of_range);
}

TEST_F(AssetManagerTests, ShouldSuccesfullyStoreAndReturnLoadedAsset)
{
    auto sut = AssetManager<interfaces::StubAsset<true>>();
    EXPECT_NO_THROW(sut.loadAsset(DUMMY_ID, DUMMY_PATH));
    EXPECT_TRUE(sut.getAsset(roen::hashString(DUMMY_ID)));
}

} // manager

} // roen