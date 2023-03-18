cmake_minimum_required(VERSION 3.0)

# Generate a list of all the source files in your project directory and its subdirectories
file(GLOB_RECURSE GRAPHICS_SOURCES "*.cpp" "*.h")

# Define the target for subproject1
add_library(graphics STATIC ${GRAPHICS_SOURCES})

# Include directories for subproject1
target_include_directories(graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

