#ifndef SPIELDA_GAME_ASSET_TEXTUREASSET_HPP
#define SPIELDA_GAME_ASSET_TEXTUREASSET_HPP

#include <roen/interfaces/IAsset.hpp>

#include <raylib.h>

namespace spielda::asset
{

class TextureAsset final : public roen::interfaces::Asset<Texture2D>
{
public:
    bool loadAsset(const std::string& path) override;
    [[nodiscard]] Texture2D get() const override;
    void freeAsset() override;
private:
    Texture2D texture_;
};

} // spielda::asset

#endif //SPIELDA_GAME_ASSET_TEXTUREASSET_HPP
