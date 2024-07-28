#ifndef SPIELDA_GAME_SYSTEMS_AIDETECT_HPP
#define SPIELDA_GAME_SYSTEMS_AIDETECT_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

class AIDetect final : public roen::interfaces::ISystem
{
public:
    explicit AIDetect(entt::registry& entityManager, entt::dispatcher& dispatcher);
    void update() const;
private:
    entt::dispatcher& eventDispatcher_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_AIDETECT_HPP