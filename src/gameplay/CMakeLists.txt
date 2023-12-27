cmake_minimum_required(VERSION 3.10)

# Generate a list of all the source files in your project directory and its subdirectories
file(GLOB_RECURSE GAMEPLAY_SOURCES "*.cpp" "*.h")

# Define the target for subproject1
add_library(gameplay STATIC ${GAMEPLAY_SOURCES})

# Include directories for subproject1
target_include_directories(gameplay PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

