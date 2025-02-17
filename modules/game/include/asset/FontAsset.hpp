#ifndef SPIELDA_GAME_ASSET_FONTASSET_HPP
#define SPIELDA_GAME_ASSET_FONTASSET_HPP

#include <roen/include/interfaces/IAsset.hpp>

#include <raylib.h>

namespace spielda::asset
{

class FontAsset final : public roen::interfaces::Asset<Font>
{
public:
    bool loadAsset(const std::filesystem::path& path) override;
    [[nodiscard]] Font get() const override;
    void freeAsset() override;
private:
    Font font_;
};

} // spielda::asset

#endif //SPIELDA_GAME_ASSET_FONTASSET_HPP