#ifndef SPIELDA_GAME_SYSTEMS_PROJECTILESPAWNER_HPP
#define SPIELDA_GAME_SYSTEMS_PROJECTILESPAWNER_HPP

#include <roen/include/interfaces/ISystem.hpp>

#include <components/CharacterSheet.hpp>
#include <components/RigidBody.hpp>
#include <components/Spell.hpp>
#include <components/Sprite.hpp>
#include <components/Transform.hpp>
#include <components/tags/CollisionMask.hpp>

#include <events/Attack.hpp>

#include <entt/signal/dispatcher.hpp>

namespace spielda::system
{

class ProjectileSpawner final : public roen::interfaces::ISystem
{
public:
    explicit ProjectileSpawner(entt::registry& entityManager, entt::dispatcher& eventDispatcher);

private:
    void onAttack(events::Attack event);
    void spawnEntity(components::CharacterSheet ownerSheet, components::Spell spell,
                     components::Sprite sprite, components::Transform transform,
                     components::RigidBody rigidBody, tags::CollisionMask collisionMask,
                     double currentTime) const;
    entt::dispatcher& eventDispatcher_;
    std::unordered_map<entt::entity, double> lastSpawnTimePerEntity_;
};

}  // namespace spielda::system

#endif  // SPIELDA_GAME_SYSTEMS_PROJECTILESPAWNER_HPP