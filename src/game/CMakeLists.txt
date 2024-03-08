target_sources(${PROJECT_NAME}
    PUBLIC
    ${INCLUDE_DIR}/game/Game.hpp
    ${INCLUDE_DIR}/game/Utils.hpp
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Game.cpp
)

add_subdirectory(scenes)