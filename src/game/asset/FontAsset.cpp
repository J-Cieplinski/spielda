#include <game/asset/FontAsset.hpp>

#include <roen/log/Logger.hpp>

#include <stdexcept>

namespace spielda::asset
{

FontAsset::~FontAsset()
{
    SDK_INFO("Freeing font raylib texture id: {0}", font_.texture.id);

    UnloadFont(font_);
}

void FontAsset::loadAsset(const std::string &path)
{
    SDK_INFO("Loading font: {0}", path);

    font_ = LoadFont(path.c_str());
    if (font_.texture.id <= 0)
    {
        throw std::runtime_error("Failed to open font with path: " + path);
    }
}

Font FontAsset::get() const
{
    return font_;
}

} // spielda::asset
