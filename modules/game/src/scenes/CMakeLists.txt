target_sources(${PROJECT_NAME}
    PUBLIC
    ${GAME_INCLUDE_DIR}/scenes/GameScene.hpp
    ${GAME_INCLUDE_DIR}/scenes/MenuScene.hpp
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/GameScene.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/MenuScene.cpp
)