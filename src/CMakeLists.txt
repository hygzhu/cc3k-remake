cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(CC3K)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(CC3K 
    main.cpp
    player.h
    player.cpp
    game.h
    game.cpp
    map.cpp
    map.h
    goblin.cpp
    goblin.h
    entity.h
)

include_directories(CC3K ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(CC3K ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})