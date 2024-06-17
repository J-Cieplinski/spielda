#ifndef SPIELDA_GAME_SYSTEMS_AIDETECTRADIUSRENDER_HPP
#define SPIELDA_GAME_SYSTEMS_AIDETECTRADIUSRENDER_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <events/Mouse.hpp>

#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

class AIDetectRadiusRender final : public roen::interfaces::ISystem
{
public:
    explicit AIDetectRadiusRender(entt::registry& entityManager, entt::dispatcher& dispatcher, const Camera2D& camera);
    void update();
private:
    void onMouseClick(events::Mouse event);

    entt::dispatcher& eventDispatcher_;
    entt::entity detectedEntity_;
    const Camera2D& camera_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_AIDETECTRADIUSRENDER_HPP