cmake_minimum_required(VERSION 3.0)

# Generate a list of all the source files in your project directory and its subdirectories
file(GLOB_RECURSE UTILS_SOURCES "*.cpp" "*.h")

# Define the target for subproject1
add_library(utils STATIC ${UTILS_SOURCES})

# Include directories for subproject1
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
