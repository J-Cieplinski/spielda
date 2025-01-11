#include <systems/CollisionPartitioned.hpp>

namespace spielda::system
{

CollisionPartitioned::CollisionPartitioned(entt::registry& entityManager, entt::dispatcher& eventDispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{eventDispatcher}
{
}

void CollisionPartitioned::update() const
{
}

} // namespace spielda::system