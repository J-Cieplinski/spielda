target_sources(${PROJECT_NAME}
    PUBLIC
    ${INCLUDE_DIR}/game/systems/CollisionRender.hpp
    ${INCLUDE_DIR}/game/systems/Render.hpp
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/CollisionRender.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Render.cpp
)