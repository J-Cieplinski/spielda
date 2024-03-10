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

bool FontAsset::loadAsset(const std::string &path)
{
    SDK_INFO("Loading font: {0}", path);

    font_ = LoadFont(path.c_str());

    return font_.texture.id != 0;
}

Font FontAsset::get() const
{
    return font_;
}

} // spielda::asset
