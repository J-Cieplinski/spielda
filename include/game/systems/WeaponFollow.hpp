#ifndef SPIELDA_GAME_SYSTEMS_WEAPONFOLLOW_HPP
#define SPIELDA_GAME_SYSTEMS_WEAPONFOLLOW_HPP

#include <roen/interfaces/ISystem.hpp>

namespace spielda::system
{

class WeaponFollow final : public roen::interfaces::ISystem
{
public:
    explicit WeaponFollow(entt::registry& entityManager);
    void update();
};

} // spielda::system



#endif //SPIELDA_GAME_SYSTEMS_WEAPONFOLLOW_HPP