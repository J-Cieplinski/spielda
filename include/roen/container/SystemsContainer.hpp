#ifndef ROEN_CONTAINER_SYSTEMSCONTAINER_HPP
#define ROEN_CONTAINER_SYSTEMSCONTAINER_HPP

#include <roen/interfaces/ISystem.hpp>
#include <roen/log/Logger.hpp>

#include <unordered_map>
#include <stdexcept>
#include <typeindex>

namespace roen::container
{

namespace
{
template <typename T>
concept DerivedFromISystem = std::is_base_of<interfaces::ISystem, T>::value;
}

class SystemsContainer
{
using SystemsMap = std::unordered_map<std::type_index, std::shared_ptr<interfaces::ISystem>>;
using SystemsIterator = SystemsMap::iterator;
using SystemsConstIterator = SystemsMap::const_iterator;
public:
    template<DerivedFromISystem SystemType, typename ...Args>
    void add(Args&& ...args);

    template<DerivedFromISystem SystemType>
    void remove();

    template<DerivedFromISystem SystemType>
    [[nodiscard]] bool hasSystem() const;

    template<DerivedFromISystem SystemType>
    SystemType& get() const;

    [[nodiscard]] SystemsIterator begin();
    [[nodiscard]] SystemsConstIterator begin() const;
    [[nodiscard]] SystemsConstIterator cbegin() const;

    [[nodiscard]] SystemsIterator end();
    [[nodiscard]] SystemsConstIterator end() const;
    [[nodiscard]] SystemsConstIterator cend() const;
private:
    SystemsMap systems_;
};

} // roen::container

/*
 * Template implementation
 */

namespace roen::container
{

template<DerivedFromISystem SystemType, typename... Args>
void SystemsContainer::add(Args&&... args)
{
    auto newSystem = std::make_shared<SystemType>(std::forward<Args>(args)...);
    const auto key = std::type_index(typeid(SystemType));
    SDK_INFO("Adding system of type: {0}", key.name());

    systems_.insert({ key, std::move(newSystem) });
}

template<DerivedFromISystem SystemType>
void SystemsContainer::remove()
{
    const auto key = std::type_index(typeid(SystemType));
    if(systems_.erase(key))
    {
        SDK_INFO("Removing system of type: {0}", key.name());
    }
}

template<DerivedFromISystem SystemType>
bool SystemsContainer::hasSystem() const
{
    const auto key = std::type_index(typeid(SystemType));
    return systems_.contains(key);
}

template<DerivedFromISystem SystemType>
SystemType& SystemsContainer::get() const
{
    const auto key = std::type_index(typeid(SystemType));
    auto system = systems_.find(key);

    if(system == systems_.end())
    {
        std:: stringstream ss;
        ss << "No system of type: " << key.name() << " present";
        throw std::out_of_range(ss.str());
    }

    return *(std::static_pointer_cast<SystemType>(system->second));
}

} // roen::container

#endif //ROEN_CONTAINER_SYSTEMSCONTAINER_HPP