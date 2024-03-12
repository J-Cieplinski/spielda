#ifndef SPIELDA_ASSETMANAGER_HPP
#define SPIELDA_ASSETMANAGER_HPP

#include <roen/interfaces/IAsset.hpp>
#include <roen/log/Logger.hpp>

#include <raylib.h>

#include <map>
#include <stdexcept>
#include <typeindex>

namespace roen::manager
{

template<typename AssetType>
requires std::is_base_of_v<interfaces::IAsset, AssetType>
class AssetManager
{
public:
    ~AssetManager();

    void loadAsset(const std::string& id, const std::string& path);
    void freeAssets();
    [[nodiscard]] AssetType getAsset(std::uint64_t id) const;
private:
    inline static std::map<std::uint64_t, AssetType> assets_;
};

} // roen::manager


/*
 * Template definition
 */

#include <roen/Utils.hpp>

namespace roen::manager
{

template<typename AssetType>
requires std::is_base_of_v<interfaces::IAsset, AssetType> AssetManager<AssetType>::~AssetManager()
{
    freeAssets();
}

template<typename AssetType>
requires std::is_base_of_v<interfaces::IAsset, AssetType>
void AssetManager<AssetType>::freeAssets()
{
    assets_.clear();
}

template<typename AssetType>
requires std::is_base_of_v<interfaces::IAsset, AssetType>
void AssetManager<AssetType>::loadAsset(const std::string &id, const std::string &path)
{
    if(assets_.find(hashString(id)) != assets_.end())
    {
        return;
    }

    AssetType asset;

    if(!asset.loadAsset(path))
    {
        std::stringstream ss;
        ss << "Failed to open font with path: " << path << " and id: " << id;
        SDK_CRITICAL(ss.str());
        throw std::runtime_error(ss.str());
    }

    assets_[hashString(id)] = asset;
}

template<typename AssetType>
requires std::is_base_of_v<interfaces::IAsset, AssetType>
AssetType AssetManager<AssetType>::getAsset(std::uint64_t id) const
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

} // roen::manager

#endif //SPIELDA_ASSETMANAGER_HPP