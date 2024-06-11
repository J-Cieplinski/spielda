#include <systems/SpriteDirection.hpp>

#include <components/Sprite.hpp>
#include <components/Transform.hpp>

#include <entt/entt.hpp>

namespace spielda::system
{

SpriteDirection::SpriteDirection(entt::registry &entityManager)
    : ISystem{entityManager}
{
}

void SpriteDirection::update()
{
    auto group = entityManager_.group<components::Transform>(entt::get<components::Sprite>);

    for(auto& entity : group)
    {
        auto transform = group.get<components::Transform>(entity);
        auto& sprite = group.get<components::Sprite>(entity);

        if(transform.previousPosition.x > transform.position.x)
        {
            sprite.srcRect.width = abs(sprite.srcRect.width) * -1;
        }
        else if(transform.previousPosition.x < transform.position.x)
        {
            sprite.srcRect.width = abs(sprite.srcRect.width);
        }
    }
}
} // spielda::system
