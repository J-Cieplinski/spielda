#ifndef SPIELDA_GAME_TYPEDEFS_HPP
#define SPIELDA_GAME_TYPEDEFS_HPP

#include <game/asset/FontAsset.hpp>
#include <game/asset/TextureAsset.hpp>

#include <roen/manager/AssetManager.hpp>

namespace spielda
{

using TextureManager = roen::manager::AssetManager<asset::TextureAsset>;
using FontManager = roen::manager::AssetManager<asset::FontAsset>;

} // spielda

#endif //SPIELDA_GAME_TYPEDEFS_HPP
