#include <asset/TextureAsset.hpp>

#include <roen/include/log/Logger.hpp>

#include <stdexcept>

namespace spielda::asset
{

bool TextureAsset::loadAsset(const std::string &path)
{
    SDK_INFO("Loading texture image: {0}", path);

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

    UnloadTexture(texture_);
}

} // spielda::asset

