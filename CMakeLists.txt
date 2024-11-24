cmake_minimum_required(VERSION 3.27)

project(spielda)

set(CMAKE_CXX_STANDARD 23)

#To force windows to create .lib files
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

set(RAYLIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/roen/dependencies/raylib/src)
set(DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)
set(MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules)
set(GAME_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/modules/game/include)

add_executable(${PROJECT_NAME})

#To enable/disable spdlog logging
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC IS_DEBUG)
    if(UNIX)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -fsanitize=undefined -fsanitize=address")
        target_link_options(${PROJECT_NAME} BEFORE PUBLIC -fsanitize=undefined PUBLIC -fsanitize=address)
    endif (UNIX)
endif ()

if(PROFILE)
    add_compile_definitions(-DPROFILE=1)
endif()

if(UNIX)
    add_compile_definitions(-DUSE_WAYLAND=ON)
endif (UNIX)

add_subdirectory(dependencies)
add_subdirectory(modules)

target_precompile_headers(${PROJECT_NAME} REUSE_FROM roen)

target_link_libraries(${PROJECT_NAME} PRIVATE
    roen)

target_include_directories(${PROJECT_NAME} PUBLIC ${LUA_INCLUDE_DIR} ${DEPENDENCIES_DIR} ${RAYLIB_DIR} ${GAME_INCLUDE_DIR} ${MODULES_DIR})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS
)
