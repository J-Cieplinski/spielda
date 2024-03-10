#include <game/asset/TextureAsset.hpp>

#include <roen/log/Logger.hpp>

#include <stdexcept>

namespace spielda::asset
{

TextureAsset::~TextureAsset()
{
    SDK_INFO("Freeing texture raylib id: {0}", texture_.id);

    UnloadTexture(texture_);
}

void TextureAsset::loadAsset(const std::string &path)
{
    SDK_INFO("Loading texture image: {0}", path);

    texture_ = LoadTexture(path.c_str());
    if (texture_.id <= 0)
    {
        throw std::runtime_error("Failed to open texture with path: " + path);
    }
}

Texture2D TextureAsset::get() const
{
    return texture_;
}

} // spielda::asset
