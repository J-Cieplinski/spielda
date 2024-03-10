target_sources(${PROJECT_NAME}
    PUBLIC
    ${INCLUDE_DIR}/game/asset/FontAsset.hpp
    ${INCLUDE_DIR}/game/asset/TextureAsset.hpp
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/FontAsset.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/TextureAsset.cpp
)