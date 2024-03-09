target_sources(${PROJECT_NAME}
    PUBLIC
    ${INCLUDE_DIR}/game/scenes/GameScene.hpp
    ${INCLUDE_DIR}/game/scenes/MenuScene.hpp
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/GameScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MenuScene.cpp
)