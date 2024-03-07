cmake_minimum_required(VERSION 3.27)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/dependencies/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(spielda)

set(CMAKE_CXX_STANDARD 20)

find_package(EnTT CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(raylib CONFIG REQUIRED)
find_package(sol2 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    EnTT::EnTT
    ${LUA_LIBRARIES}
    raylib
    sol2
    spdlog::spdlog)

target_include_directories(${PROJECT_NAME} PRIVATE ${LUA_INCLUDE_DIR})
