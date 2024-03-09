#ifndef SPIELDA_ASSETMANAGER_HPP
#define SPIELDA_ASSETMANAGER_HPP

#include <roen/log/Logger.hpp>

#include <raylib.h>

#include <map>
#include <stdexcept>
#include <typeindex>

namespace roen::manager
{

template<typename AssetType>
class AssetManager
{
public:
    ~AssetManager();

    void loadAsset(const std::string& id, const std::string& path);
    void freeAssets();
    [[nodiscard]] AssetType getAsset(std::uint32_t id) const;
private:
    std::map<std::uint32_t, AssetType> assets_;
};

} // roen::manager


/*
 * Template definition
 */

#include <roen/Utils.hpp>

namespace roen::manager
{

template<typename AssetType>
AssetManager<AssetType>::~AssetManager()
{
    freeAssets();
}

template<typename AssetType>
AssetType AssetManager<AssetType>::getAsset(std::uint32_t id) const
{
    try
    {
        return assets_.at(id);
    }
    catch (std::out_of_range& e)
    {
        SDK_CRITICAL("{0} id: {1} does not exist", std::type_index(typeid(AssetType)).name(), id);
        throw e;
    }
}

//Texture2D

template<>
void AssetManager<Texture2D>::loadAsset(const std::string& id, const std::string& path)
{
    SDK_INFO("Loading texture id: {0} with image: {1}", id, path);

    auto texture = LoadTexture(path.c_str());
    if (texture.id <= 0)
    {
        SDK_WARN("Failed to open texture image id: {0} with path: {1}", id, path);
    }

    assets_[hashString(id)] = texture;
}

template<>
void AssetManager<Texture2D>::freeAssets()
{
    SDK_INFO("Freeing all textures");
    for (const auto& [key, texture] : assets_)
    {
        UnloadTexture(texture);
    }
    assets_.clear();
}

//Font

template<>
void AssetManager<Font>::loadAsset(const std::string& id, const std::string& path)
{
    SDK_INFO("Loading Font id: {0} with font: {1}", id, path);

    auto font = LoadFont(path.c_str());
    if (font.texture.id <= 0)
    {
        SDK_WARN("Failed to open font id: {0} with path: {1}", id, path);
    }

    assets_[hashString(id)] = font;
}

template<>
void AssetManager<Font>::freeAssets()
{
    SDK_INFO("Freeing all fonts");
    for(const auto& [key, font] : assets_)
    {
        UnloadFont(font);
    }
    assets_.clear();
}

} // roen::manager

#endif //SPIELDA_ASSETMANAGER_HPP