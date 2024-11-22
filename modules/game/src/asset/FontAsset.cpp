#include <asset/FontAsset.hpp>

#include <roen/include/log/Logger.hpp>

#include <stdexcept>

namespace spielda::asset
{

bool FontAsset::loadAsset(const std::filesystem::path& path)
{
    SDK_INFO("Loading font: {0}", path.string());

    font_ = LoadFont(path.c_str());

    return font_.texture.id != 0;
}

Font FontAsset::get() const
{
    return font_;
}

void FontAsset::freeAsset()
{
    SDK_INFO("Freeing font raylib texture id: {0}", font_.texture.id);

    UnloadFont(font_);
}

} // spielda::asset
