#include <systems/AIMove.hpp>

#include <Utils.hpp>
#include <components/AI.hpp>
#include <components/CircleCollider.hpp>
#include <components/RigidBody.hpp>

#include <roen/include/algorithms/search/Pathfinding.hpp>
#include <roen/include/log/Logger.hpp>

#include <entt/entity/registry.hpp>

#include <raymath.h>

#include <ranges>
#include <queue>

namespace spielda::system
{

AIMove::AIMove(entt::registry& entityManager, entt::dispatcher& dispatcher)
    : ISystem{entityManager}
    , eventDispatcher_{dispatcher}
{
    eventDispatcher_.sink<events::AIDetectedEnemy>().connect<&AIMove::onDetect>(this);
}

void AIMove::update()
{
    auto view = entityManager_.view<components::AI, components::CircleCollider, components::RigidBody>();
    constexpr std::uint16_t velocity {20};
    for(auto& [entity, nodes] : travelingEntities_)
    {
        if(!entityManager_.valid(entity))
        {
            entitiesToRemoveFromTravel_.push_back(entity);
            continue;
        }

        const auto aiCollider = view.get<components::CircleCollider>(entity);

        auto& aiVelocity = view.get<components::RigidBody>(entity).velocity;

        if(!nodes.empty()
            && nodes.front().contains({aiCollider.position.x, aiCollider.position.y})
            && aiCollider.collisionType != CollisionType::WALL)
        {
            nodes.pop_front();
        }

        const auto& aiState = view.get<components::AI>(entity).state;

        if(nodes.empty() || aiState == components::AIState::IDLE)
        {
            entitiesToRemoveFromTravel_.push_back(entity);
            aiVelocity = {0, 0};
            continue;
        }

        const auto& currentNode = nodes.front();
        const auto& currentNodePos = currentNode.getPosition();
        const auto& currentNodeSize = currentNode.getSize();

        Vector2 currentNodeCenter = toRayVector(currentNodePos + (currentNodeSize / 2.f));

        auto moveVector = Vector2Normalize(Vector2Subtract(currentNodeCenter, aiCollider.position));
        aiVelocity = Vector2Scale(moveVector, velocity);
    }

    for(const auto entityToRemove : entitiesToRemoveFromTravel_)
    {
        travelingEntities_.erase(entityToRemove);
    }

    entitiesToRemoveFromTravel_.clear();
}

void AIMove::onDetect(events::AIDetectedEnemy event)
{
    const auto view = entityManager_.view<components::AI, components::CircleCollider>();

    auto& aiState = view.get<components::AI>(event.aiEntity).state;
    aiState = components::AIState::FOLLOWING;

    const auto aiCollider = view.get<components::CircleCollider>(event.aiEntity).position;

    const auto& pathfindingGraph = entityManager_.ctx().get<roen::data_structure::Graph<roen::data_structure::MapNode>>();
    auto closestAINode = getClosestMapNode(aiCollider, pathfindingGraph);
    auto closestPlayerNode = getClosestMapNode(event.detectedEntityPosition, pathfindingGraph);
    auto path = roen::algorithms::a_star(closestAINode, closestPlayerNode, pathfindingGraph, roen::algorithms::manhattanDistance);
    auto travelOrder = roen::algorithms::getNodeOrderFromPath(closestAINode, closestPlayerNode, path);

    travelingEntities_[event.aiEntity] = std::list(travelOrder.begin(), travelOrder.end());
}

roen::data_structure::MapNode AIMove::getClosestMapNode(const Vector2& position,
                                                        const roen::data_structure::Graph<roen::data_structure::MapNode>& pathfindingGraph) const
{
    std::queue<roen::data_structure::MapNode> nodes{};

    for(const auto& node : pathfindingGraph.getEdges() | std::ranges::views::keys)
    {
        if(node.contains({position.x, position.y}))
        {
            nodes.push(node);
        }
    }

    roen::data_structure::MapNode currentClosestNode = nodes.front();
    nodes.pop();

    Vector2 currentClosestNodeV = toRayVector(currentClosestNode.getPosition());

    while(!nodes.empty())
    {
        auto consideredNode = nodes.front();
        nodes.pop();

        const Vector2 consideredNodeV = toRayVector(consideredNode.getPosition());

        if(Vector2Distance(position, currentClosestNodeV) > Vector2Distance(position, consideredNodeV))
        {
            currentClosestNodeV = consideredNodeV;
            currentClosestNode = consideredNode;
        }
    }

    return currentClosestNode;
}

} // spielda::system