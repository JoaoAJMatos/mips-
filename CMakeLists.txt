# Set minimum version of CMake.
cmake_minimum_required(VERSION 3.15)

# Set project name and version.
set(PROJECT_NAME mips++)
project(${PROJECT_NAME} LANGUAGES CXX VERSION 0.1.0)

# Set C++ standard.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the include directories.
include_directories("include")

# Set the compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Werror")

# Set the build type.
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Set the output directory.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the source files.
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

# Add the executable.
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
