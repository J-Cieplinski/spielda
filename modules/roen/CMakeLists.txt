project(roen)

add_library(${PROJECT_NAME} SHARED)

find_package(EnTT CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)
find_package(sol2 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_sources(${PROJECT_NAME}
    PUBLIC
    ${INCLUDE_DIR}/Utils.hpp
    ${INCLUDE_DIR}/interfaces/IAsset.hpp
    ${INCLUDE_DIR}/interfaces/IScene.hpp
    ${INCLUDE_DIR}/interfaces/ISystem.hpp
)

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PUBLIC
    EnTT::EnTT
    ${LUA_LIBRARIES}
    nlohmann_json::nlohmann_json
    raylib
    sol2
    spdlog::spdlog)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR} ${DEPENDENCIES_DIR} ${LUA_INCLUDE_DIR})