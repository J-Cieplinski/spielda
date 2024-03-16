cmake_minimum_required(VERSION 3.27)

#To force usage of vcpkg cmake toolchain
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/dependencies/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(spielda)

set(CMAKE_CXX_STANDARD 20)

#To force windows to create .lib files
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(Lua REQUIRED)
find_package(sol2 CONFIG REQUIRED)

add_executable(${PROJECT_NAME})

#To enable/disable spdlog logging
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PUBLIC IS_DEBUG)
endif ()

add_subdirectory(src)
add_subdirectory(tests)

target_sources(${PROJECT_NAME}
    PRIVATE
    main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    roen)

target_include_directories(${PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${PROJECT_NAME}> $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}>
    COMMAND_EXPAND_LISTS
)
