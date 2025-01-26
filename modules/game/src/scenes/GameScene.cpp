#include <scenes/GameScene.hpp>

#include <CoreConfig.hpp>
#include <MapLoader.hpp>
#include <SpatialGrid.hpp>
#include <Typedefs.hpp>

#include <components/AI.hpp>
#include <components/AttachedEntities.hpp>
#include <components/CharacterSheet.hpp>
#include <components/Collider.hpp>
#include <components/Dirty.hpp>
#include <components/Health.hpp>
#include <components/Player.hpp>
#include <components/RigidBody.hpp>
#include <components/Spell.hpp>
#include <components/Sprite.hpp>
#include <components/Transform.hpp>
#include <components/Weapon.hpp>
#include <components/WieldedWeapon.hpp>

#include <components/tags/Attachment.hpp>
#include <components/tags/CollisionMask.hpp>

#include <systems/AIDetect.hpp>
#include <systems/AIDetectRadiusRender.hpp>
#include <systems/AIMove.hpp>
#include <systems/Animation.hpp>
#include <systems/CollisionPartitioned.hpp>
#include <systems/CollisionRender.hpp>
#include <systems/Damage.hpp>
#include <systems/DebugRender.hpp>
#include <systems/GraphRender.hpp>
#include <systems/Keyboard.hpp>
#include <systems/MeleeCombat.hpp>
#include <systems/Mouse.hpp>
#include <systems/Movement.hpp>
#include <systems/ProjectileSpawner.hpp>
#include <systems/Render.hpp>
#include <systems/WallBoundaries.hpp>
#include <systems/WeaponFollow.hpp>

#include <roen/include/Utils.hpp>
#include <roen/include/log/Logger.hpp>
#include <roen/include/log/formatters/entity.hpp>

#include <raymath.h>
#include <entt/entt.hpp>

#include <ranges>

namespace spielda::scenes
{

GameScene::GameScene(roen::manager::GameSceneManager& gameSceneManager)
    : IScene{gameSceneManager}
    , deltaTime_{0}
    , renderTexture_{LoadRenderTexture(RENDER_WIDTH, RENDER_HEIGHT)}
    , camera_{Vector2{0, 0}, Vector2{0, 0}, 0.f, 1.5f}
    , debugRender_{false}
{
    initSystems();

    entityManager_.ctx().emplace<TextureManager>();

    entityManager_.on_construct<components::Sprite>()
        .connect<[&](entt::registry& reg, entt::entity e) { reg.emplace<components::Dirty>(e); }>();

    eventDisptacher_.sink<events::DebugSwitch>().connect<&GameScene::switchDebug>(this);
    SET_APP_LOG_LEVEL(LOG_LEVEL_INFO);
}

void GameScene::handleInput()
{
}

void GameScene::render()
{
    float scale = std::min(static_cast<float>(GetScreenWidth()) / RENDER_WIDTH,
                           static_cast<float>(GetScreenHeight()) / RENDER_HEIGHT);

    BeginTextureMode(renderTexture_);
    ClearBackground(RAYWHITE);

    systems_.get<system::Render>().update();
    if (debugRender_)
    {
        systems_.get<system::CollisionRender>().update();
        systems_.get<system::DebugRender>().update();
        systems_.get<system::AIDetectRadiusRender>().update();
        if (systems_.hasSystem<system::GraphRender>())
        {
            systems_.get<system::GraphRender>().update();
        }
    }

    DrawFPS(5, GetScreenHeight() - 20);

    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);

    DrawTexturePro(renderTexture_.texture,
                   Rectangle{0.f, 0.f, static_cast<float>(renderTexture_.texture.width),
                             static_cast<float>(-(renderTexture_.texture.height))},
                   Rectangle{
                       (GetScreenWidth() - RENDER_WIDTH * scale) * 0.5f,
                       (GetScreenHeight() - RENDER_HEIGHT * scale) * 0.5f,
                       RENDER_WIDTH * scale,
                       RENDER_HEIGHT * scale,
                   },
                   Vector2{0, 0}, 0.f, WHITE);
    EndDrawing();
}

void GameScene::update()
{
    updateDeltaTime();
    systems_.get<system::Keyboard>().update();
    systems_.get<system::Mouse>().update();
    systems_.get<system::AIDetect>().update();
    systems_.get<system::AIMove>().update();
    systems_.get<system::Movement>().update(deltaTime_);
    systems_.get<system::MeleeCombat>().update(deltaTime_);
    systems_.get<system::WeaponFollow>().update();
    systems_.get<system::CollisionPartitioned>().update();
    systems_.get<system::Damage>().update();
    systems_.get<system::Animation>().update();
}

void GameScene::obscured()
{
}

void GameScene::revealed()
{
    APP_INFO("Entered GameScene");
    entityManager_.ctx().get<TextureManager>().loadAsset("fireball",
                                                         "assets/textures/fireball.png");

    loadLevel("assets/definitions/levels/dungeon.json");

#ifdef PROFILE
    for (auto i : std::ranges::iota_view{1, 100})
    {
        spawnDebugEntity();
    }
#endif
}

void GameScene::quit()
{
}

void GameScene::loadLevel(std::filesystem::path path)
{
    using json = nlohmann::json;

    auto mapLoader = MapLoader(entityManager_);
    mapLoader.loadMap(path);
    entityManager_.ctx().emplace<roen::data_structure::Graph<roen::data_structure::MapNode>>(
        mapLoader.getGraph());
    auto mapSize = mapLoader.getMapSize();
    auto tileSize = mapLoader.getTileSize();
    auto realMapSize = mapSize * tileSize;
    auto& grid = entityManager_.ctx().emplace<SpatialGrid>(mapSize.x, mapSize.y, tileSize.x);

    systems_.get<system::Render>().preRenderMap(realMapSize.x, realMapSize.y);

    APP_INFO("Loading level: {0}", path.string());

    std::ifstream file{path};
    if (!file.is_open())
    {
        APP_CRITICAL("Failed to open level file: {0}", path.string());
        return;
    }

    auto level = json::parse(file);

    loadHero(level);

    grid.initGrid(entityManager_);
}

void GameScene::loadHero(const nlohmann::json& level)
{
    constexpr std::uint32_t layer = 5;
    constexpr std::uint32_t layerOrder = 1;

    constexpr Rectangle weaponSrcRect{.x = 128.f, .y = 128.f, .width = 16.f, .height = 16.f};

    constexpr Vector2 weaponOrigin{.x = -8, .y = -16};

    constexpr Vector2 weaponPosition{.x = 14, .y = 13};

    auto weapon = entityManager_.create();
    auto hero = entityManager_.create();

    components::BoxCollider weaponCollider{.position = weaponPosition,
                                           .previousPosition = weaponPosition,
                                           .size = Vector2{14, 12},
                                           .collisionType = CollisionType::NONE};

    entityManager_.emplace<components::Weapon>(weapon, hero, 20u);
    entityManager_.emplace<components::Collider>(weapon, weaponCollider);
    entityManager_.emplace<components::Transform>(weapon, weaponPosition, weaponPosition,
                                                  Vector2{1, 1}, 0.f);
    entityManager_.emplace<components::Sprite>(weapon, Vector2{16, 16}, weaponOrigin, weaponSrcRect,
                                               layer + 1, layerOrder, roen::hashString("dungeon"),
                                               false);
    entityManager_.emplace<tags::CollisionMask>(
        weapon, tags::MaskLayer::PLAYER | tags::MaskLayer::DECORATION | tags::MaskLayer::WEAPON);
    entityManager_.emplace<tags::Attachment>(weapon);

    const auto player = level["player"];

    const Vector2 spriteSize{.x = player["sprite"]["size"], .y = player["sprite"]["size"]};

    const Rectangle srcRect{
        .x = player["sprite"]["source"]["x"],
        .y = player["sprite"]["source"]["y"],
        .width = spriteSize.x,
        .height = spriteSize.y,
    };

    const Vector2 absolutePosition{.x = player["position"]["x"], .y = player["position"]["y"]};

    const Vector2 weaponColliderAttachOffset = {.x = 7, .y = 3 - spriteSize.y / 2};

    components::Sprite heroSprite{
        .size = spriteSize,
        .origin = Vector2Scale(spriteSize, -0.5f),
        .srcRect = srcRect,
        .layer = player["layer"],
        .zIndexInLayer = player["layerOrder"],
        .guid = roen::hashString(player["sprite"]["name"]),
        .isFixed = false,
    };

    const Vector2 colliderPosition = absolutePosition;

    components::CircleCollider playerCollider{.position = absolutePosition,
                                              .previousPosition = absolutePosition,
                                              .radius = 6,
                                              .collisionType = CollisionType::NONE};

    entityManager_.emplace<components::Sprite>(hero, heroSprite);
    entityManager_.emplace<components::Transform>(hero, absolutePosition, absolutePosition,
                                                  Vector2{1, 1}, 0.f);
    entityManager_.emplace<components::Collider>(hero, playerCollider);
    entityManager_.emplace<components::RigidBody>(hero, Vector2{0, 0}, Vector2{1, 0});
    entityManager_.emplace<components::Player>(hero);
    entityManager_.emplace<components::WieldedWeapon>(hero, weapon, weaponColliderAttachOffset);
    entityManager_.emplace<components::CharacterSheet>(hero, 10, 10);
    entityManager_.emplace<components::AttachedEntities>(hero, std::set{weapon});

    constexpr components::Spell spell{
        .velocity = {60.f, 60.f},
        .size = {64.f, 64.f},
        .origin = {-32.f, -32.f},
        .srcRect = {.x = 0, .y = 0, .width = 64, .height = 64},
        .damage = 20,
        .spawnFrequency = 1.f,
        .guid = roen::hashString("fireball"),
    };

    entityManager_.emplace<components::Spell>(hero, spell);

    entityManager_.emplace<tags::CollisionMask>(hero,
                                                tags::MaskLayer::PLAYER | tags::MaskLayer::MOVING);
}

void GameScene::updateDeltaTime()
{
    constexpr float MIN_FPS{30};
    constexpr float MAX_FRAMETIME{1 / MIN_FPS};

    deltaTime_ = std::min(GetFrameTime(), MAX_FRAMETIME);
}

void GameScene::initSystems()
{
    systems_.add<system::AIDetect>(entityManager_, eventDisptacher_);
    systems_.add<system::AIDetectRadiusRender>(entityManager_, eventDisptacher_, camera_);
    systems_.add<system::AIMove>(entityManager_, eventDisptacher_);
    systems_.add<system::Animation>(entityManager_);
    systems_.add<system::CollisionPartitioned>(entityManager_, eventDisptacher_);
    systems_.add<system::Damage>(entityManager_, eventDisptacher_);
    systems_.add<system::DebugRender>(entityManager_, camera_);
    systems_.add<system::GraphRender>(entityManager_, camera_);
    systems_.add<system::CollisionRender>(entityManager_, camera_);
    systems_.add<system::WallBoundaries>(entityManager_, eventDisptacher_);
    systems_.add<system::Keyboard>(entityManager_, eventDisptacher_);
    systems_.add<system::MeleeCombat>(entityManager_, eventDisptacher_);
    systems_.add<system::Mouse>(entityManager_, eventDisptacher_);
    systems_.add<system::Movement>(entityManager_);
    systems_.add<system::ProjectileSpawner>(entityManager_, eventDisptacher_);
    systems_.add<system::Render>(entityManager_, camera_);
    systems_.add<system::WeaponFollow>(entityManager_);
}

void GameScene::switchDebug(const events::DebugSwitch& event)
{
    debugRender_ = event.switchRender ? !debugRender_ : debugRender_;

    if (event.switchAppLogging)
    {
        if (GET_SDK_LOG_LEVEL() == LOG_LEVEL_OFF)
        {
            SET_APP_LOG_LEVEL(LOG_LEVEL_INFO);
        }
        else
        {
            SET_APP_LOG_LEVEL(LOG_LEVEL_OFF);
        }
    }

    if (event.switchSdkLogging)
    {
        if (GET_APP_LOG_LEVEL() == LOG_LEVEL_OFF)
        {
            SET_SDK_LOG_LEVEL(LOG_LEVEL_INFO);
        }
        else
        {
            SET_SDK_LOG_LEVEL(LOG_LEVEL_OFF);
        }
    }
}

void GameScene::spawnDebugEntity()
{
    auto debugEnt = entityManager_.create();
    constexpr Rectangle srcRect{.x = 0.f, .y = 128.f, .width = 16.f, .height = 16.f};
    constexpr std::uint32_t layer = 5;
    constexpr std::uint32_t layerOrder = 1;
    constexpr Vector2 position{.x = 81, .y = 128};
    constexpr Vector2 colliderPosition{.x = 82, .y = 130};

    components::CircleCollider entityCollider{.position = colliderPosition,
                                              .previousPosition = colliderPosition,
                                              .radius = 7,
                                              .collisionType = CollisionType::NONE};

    entityManager_.emplace<components::Sprite>(debugEnt, Vector2{16, 16}, Vector2{0, 0}, srcRect,
                                               layer, layerOrder, roen::hashString("dungeon"),
                                               false);
    entityManager_.emplace<components::Collider>(debugEnt, entityCollider);
    entityManager_.emplace<components::Transform>(debugEnt, position, position, Vector2{1, 1}, 0.f);
    entityManager_.emplace<components::RigidBody>(debugEnt, Vector2{0, 0}, Vector2{1, 0});
    entityManager_.emplace<components::Health>(debugEnt, 100u, 100u);
    entityManager_.emplace<components::AI>(debugEnt, 80.f);
    entityManager_.emplace<tags::CollisionMask>(debugEnt,
                                                tags::MaskLayer::ENEMY | tags::MaskLayer::MOVING);

    APP_INFO("Added debug entity {0}", debugEnt);
}

}  // namespace spielda::scenes