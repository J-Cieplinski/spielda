#include <systems/AIMove.hpp>

#include <components/AI.hpp>
#include <components/BoxCollider.hpp>
#include <components/RigidBody.hpp>

#include <roen/include/algorithms/search/Pathfinding.hpp>
#include <roen/include/log/Logger.hpp>

#include <entt/entity/registry.hpp>

#include <raymath.h>

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
    constexpr std::uint16_t velocity {20};
    for(auto& [entity, nodes] : travelingEntities_)
    {
        const auto aiCollider = entityManager_.get<components::BoxCollider>(entity);
        Vector2 aiColliderCenter = Vector2Add(aiCollider.position, Vector2Scale(aiCollider.size, 0.5f));

        auto& aiVelocity = entityManager_.get<components::RigidBody>(entity).velocity;

        bool popped {false};
        if(!nodes.empty() && nodes.front().contains({aiCollider.position.x, aiCollider.position.y}))
        {
            nodes.pop_front();
            popped = true;
        }

        if(nodes.empty())
        {
            entitiesToRemoveFromTravel_.push_back(entity);
            aiVelocity = {0, 0};
            continue;
        }

        if(popped)
        {
            const auto& currentNode = nodes.front();
            const auto& currentNodePos = currentNode.getPosition();
            const auto& currentNodeSize = currentNode.getSize();

            Vector2 currentNodeCenter = {
                    .x = static_cast<float>(currentNodePos.first + currentNodeSize.first / 2),
                    .y = static_cast<float>(currentNodePos.second + currentNodeSize.second / 2)
            };
            APP_INFO("Current node coords\nx: {0}, y: {1}", currentNodePos.first, currentNodePos.second);

            auto moveVector = Vector2Normalize(Vector2Subtract(currentNodeCenter, aiColliderCenter));
            aiVelocity = Vector2Scale(moveVector, velocity);
        }
    }

    for(const auto entityToRemove : entitiesToRemoveFromTravel_)
    {
        travelingEntities_.erase(entityToRemove);
    }

    entitiesToRemoveFromTravel_.clear();
}

void AIMove::onDetect(events::AIDetectedEnemy event)
{
    auto& aiState = entityManager_.get<components::AI>(event.aiEntity).state;
    aiState = components::AIState::FOLLOWING;

    const auto aiCollider = entityManager_.get<components::BoxCollider>(event.aiEntity).position;
    auto& aiVelocity = entityManager_.get<components::RigidBody>(event.aiEntity).velocity;

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

    roen::data_structure::MapNode currentClosestNode;

    for(const auto& [node, edge] : pathfindingGraph.getEdges())
    {
        if(node.contains({position.x, position.y}))
        {
            nodes.push(node);
        }
    }

    currentClosestNode = nodes.front();
    nodes.pop();

    Vector2 currentClosestNodeV {
            .x = static_cast<float>(currentClosestNode.getPosition().first),
            .y = static_cast<float>(currentClosestNode.getPosition().second)
    };

    while(!nodes.empty())
    {
        auto consideredNode = nodes.front();
        nodes.pop();

        Vector2 consideredNodeV {
            .x = static_cast<float>(consideredNode.getPosition().first),
            .y = static_cast<float>(consideredNode.getPosition().second)
        };

        if(Vector2Distance(position, currentClosestNodeV) > Vector2Distance(position, consideredNodeV))
        {
            currentClosestNodeV = consideredNodeV;
            currentClosestNode = consideredNode;
        }
    }

    return currentClosestNode;
}

} // spielda::system