target_sources(${PROJECT_NAME}
    PUBLIC
    ${INCLUDE_DIR}/game/Game.hpp
    ${INCLUDE_DIR}/game/MapLoader.hpp
    ${INCLUDE_DIR}/game/components/Sprite.hpp
    ${INCLUDE_DIR}/game/components/Transform.hpp
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/MapLoader.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp
)

add_subdirectory(asset)
add_subdirectory(scenes)
add_subdirectory(systems)