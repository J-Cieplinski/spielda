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

} // spielda::asset
