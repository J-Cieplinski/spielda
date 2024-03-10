target_sources(${PROJECT_NAME}
    PUBLIC
    ${INCLUDE_DIR}/roen/manager/AssetManager.hpp
    ${INCLUDE_DIR}/roen/manager/GameSceneManager.hpp
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/GameSceneManager.cpp
)