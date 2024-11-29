#include <systems/Animation.hpp>

#include <components/Animation.hpp>
#include <components/Sprite.hpp>

namespace spielda::system
{

Animation::Animation(entt::registry& entityManager)
    : ISystem{entityManager}
{
}

void Animation::update() const
{
    auto group = entityManager_.group<components::Animation>(entt::get<components::Sprite>);
    for (auto entity : group)
    {
        auto& animation = group.get<components::Animation>(entity);
        auto& sprite = group.get<components::Sprite>(entity);

        if((animation.currentFrame + 1 >= animation.numberOfFrames) && not animation.shouldLoop)
        {
            continue;
        }

        animation.currentFrame = static_cast<std::uint32_t>(((GetTime() - animation.startTime) * animation.frameRateSpeed)) % animation.numberOfFrames;

        if(animation.type == components::AnimationType::HORIZONTAL)
        {
            sprite.srcRect.x = animation.currentFrame * sprite.srcRect.width;
        }
        else if(animation.type == components::AnimationType::VERTICAL)
        {
            sprite.srcRect.y = animation.currentFrame * sprite.srcRect.height;
        }
    }
}

} // namespace spielda::system