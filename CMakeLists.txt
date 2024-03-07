cmake_minimum_required(VERSION 3.27)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/dependencies/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(spielda)

set(CMAKE_CXX_STANDARD 20)

add_compile_definitions(IS_DEBUG)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
    set(BUILD_SHARED_LIBS TRUE)
endif()

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package(EnTT CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(raylib CONFIG REQUIRED)
find_package(sol2 CONFIG REQUIRED)

add_subdirectory(src)

add_executable(${PROJECT_NAME})

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
