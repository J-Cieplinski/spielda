project(roen)

add_library(${PROJECT_NAME} SHARED)

find_package(EnTT CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(raylib CONFIG REQUIRED)
find_package(sol2 CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_sources(${PROJECT_NAME}
    PUBLIC
    ${INCLUDE_DIR}/roen//Utils.hpp
    ${INCLUDE_DIR}/roen/interfaces/IScene.hpp
)

add_subdirectory(log)
add_subdirectory(manager)

target_link_libraries(${PROJECT_NAME} PUBLIC
    EnTT::EnTT
    ${LUA_LIBRARIES}
    nlohmann_json::nlohmann_json
    raylib
    sol2
    spdlog::spdlog)

target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIR} ${LUA_INCLUDE_DIR})