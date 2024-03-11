#ifndef ROEN_INTERFACES_ISYSTEM_HPP
#define ROEN_INTERFACES_ISYSTEM_HPP

#include <entt/entity/fwd.hpp>

namespace roen::interfaces
{

class ISystem
{
public:
    explicit ISystem(const entt::registry& entityManager)
        : entityManager_{entityManager}
    {
    }

    virtual void update() = 0;

    virtual ~ISystem() = default;

private:
    const entt::registry& entityManager_;
};

} // roen::interfaces

#endif //ROEN_INTERFACES_ISYSTEM_HPP
