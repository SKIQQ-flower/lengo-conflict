cmake_minimum_required(VERSION 3.15)
project(RaylibCppExample LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME raylib-cpp
  GITHUB_REPOSITORY RobLoach/raylib-cpp
  GIT_TAG master
)

CPMAddPackage(
  NAME tomlpp
  GITHUB_REPOSITORY marzer/tomlplusplus
  GIT_TAG master
)

find_package(raylib QUIET)

if(NOT raylib_FOUND)
  message(STATUS "Raylib not found, downloading...")
  CPMAddPackage(
    NAME raylib
    GITHUB_REPOSITORY raysan5/raylib
    GIT_TAG master
  )
endif()

add_executable(${PROJECT_NAME}
  main.cpp
  engine/scenes/game_scene.cpp
  engine/scenes/menu_scene.cpp
  engine/scenes/scene_manager.cpp
)

target_include_directories(${PROJECT_NAME}
  PRIVATE ${raylib-cpp_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib_cpp raylib tomlplusplus::tomlplusplus)

if(UNIX AND NOT APPLE)
  target_link_libraries(${PROJECT_NAME} PRIVATE m pthread dl rt X11)
endif()
