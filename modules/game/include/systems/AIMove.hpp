#ifndef SPIELDA_GAME_SYSTEMS_AIDMOVE_HPP
#define SPIELDA_GAME_SYSTEMS_AIDMOVE_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <events/AIDetectedEnemy.hpp>

#include <roen/include/data_structure/Graph.hpp>
#include <roen/include/data_structure/MapNode.hpp>

#include <entt/signal/dispatcher.hpp>

#include <map>
#include <list>

namespace spielda::system
{

struct TravelingEntities
{
    std::list<roen::data_structure::MapNode> path;
    entt::entity entity;
};

class AIMove final : public roen::interfaces::ISystem
{
public:
    explicit AIMove(entt::registry& entityManager, entt::dispatcher& dispatcher);
    void update();
private:
    void onDetect(events::AIDetectedEnemy event);
    roen::data_structure::MapNode getClosestMapNode(const Vector2& position,
                                                    const roen::data_structure::Graph<roen::data_structure::MapNode>& pathfindingGraph) const;

    entt::dispatcher& eventDispatcher_;
    std::map<entt::entity, std::list<roen::data_structure::MapNode>> travelingEntities_;
    std::vector<entt::entity> entitiesToRemoveFromTravel_;
};

inline bool operator<(const TravelingEntities rhs, const TravelingEntities& lhs)
{
    return rhs.entity < lhs.entity;
}

} // spielda::system

#endif //SPIELDA_GAME_SYSTEMS_AIDMOVE_HPP