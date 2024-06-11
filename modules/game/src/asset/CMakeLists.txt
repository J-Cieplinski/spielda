target_sources(${PROJECT_NAME}
    PUBLIC
    ${GAME_INCLUDE_DIR}/asset/FontAsset.hpp
    ${GAME_INCLUDE_DIR}/asset/TextureAsset.hpp
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/FontAsset.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TextureAsset.cpp
)