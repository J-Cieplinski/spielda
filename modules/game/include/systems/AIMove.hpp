#ifndef SPIELDA_GAME_SYSTEMS_AIDMOVE_HPP
#define SPIELDA_GAME_SYSTEMS_AIDMOVE_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <events/AIDetectedEnemy.hpp>

#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

class AIMove final : public roen::interfaces::ISystem
{
public:
    explicit AIMove(entt::registry& entityManager, entt::dispatcher& dispatcher);
    void onDetect(events::AIDetectedEnemy event);
private:
    entt::dispatcher& eventDispatcher_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_AIDMOVE_HPP