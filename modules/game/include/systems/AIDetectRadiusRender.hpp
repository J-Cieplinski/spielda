#ifndef SPIELDA_GAME_SYSTEMS_AIDETECTRADIUSRENDER_HPP
#define SPIELDA_GAME_SYSTEMS_AIDETECTRADIUSRENDER_HPP

#include <systems/IRenderSystem.hpp>

#include <events/Mouse.hpp>

#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

class AIDetectRadiusRender final : public IRenderSystem
{
public:
    explicit AIDetectRadiusRender(entt::registry& entityManager, entt::dispatcher& dispatcher, const Camera2D& camera);
    void update() override;
private:
    void onMouseClick(events::Mouse event);

    entt::dispatcher& eventDispatcher_;
    entt::entity detectedEntity_;
};

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_AIDETECTRADIUSRENDER_HPP