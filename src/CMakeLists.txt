cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

project(CC3K)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

# Generate a list of all the source files in your project directory and its subdirectories
file(GLOB_RECURSE SOURCES "*.cpp" "*.h")

add_executable(CC3K 
    ${SOURCES}
)



add_subdirectory(entity)
add_subdirectory(geometry)
add_subdirectory(room)


include_directories(CC3K ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
target_link_libraries(CC3K ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})