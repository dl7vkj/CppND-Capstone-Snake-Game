cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} src)

add_executable(SnakeGame
    src/main.cpp
    src/game.cpp
    # src/controller.cpp
    src/renderer.cpp
    src/texture.cpp
    # src/component.cpp
    # src/texture_component.cpp
    # src/star_component.cpp
    # src/actor.cpp
    # src/player.cpp
    # src/alien_actor.cpp
    # src/bullet_actor.cpp
    # src/star.cpp
    src/utility.cpp
    src/game_object.cpp
    src/texture_graphics_component.cpp
)
#string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(SnakeGame ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
