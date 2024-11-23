#include <asset/TextureAsset.hpp>

#include <roen/include/log/Logger.hpp>

#include <raylib.h>

#include <stdexcept>

namespace spielda::asset
{

bool TextureAsset::loadAsset(const std::filesystem::path& path)
{
    SDK_INFO("Loading texture image: {0}", path.string());

    texture_ = LoadTexture(path.c_str());
    return texture_.id != 0;
}

Texture2D TextureAsset::get() const
{
    return texture_;
}

void TextureAsset::freeAsset()
{
    SDK_INFO("Freeing texture raylib id: {0}", texture_.id);

    if(IsTextureValid(texture_))
    {
        UnloadTexture(texture_);
    }
}

} // spielda::asset

