cmake_minimum_required(VERSION 3.20)
project(AdventOfCode2024)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(include)

# Find packages
find_package(Threads REQUIRED)

# Enable compile commands for LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source files
file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/utils/*.cpp" "src/days/*.cpp")
file(GLOB_RECURSE LIBRARY_SOURCES "src/*.cpp" "src/utils/*.cpp" "src/days/*.cpp")

# Create a library with the common code (excluding main.cpp)
list(FILTER LIBRARY_SOURCES EXCLUDE REGEX "main\\.cpp$")
add_library(aoc2024_lib ${LIBRARY_SOURCES})

# Create the main executable
add_executable(aoc2024 main.cpp)

# Create separate executables for each day (optional)
# This allows running individual days if needed
# For now, we'll have one main executable that can run any day

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(aoc2024_lib PRIVATE -Wall -Wextra)
    target_compile_options(aoc2024 PRIVATE -Wall -Wextra -O3)
elseif(MSVC)
    target_compile_options(aoc2024_lib PRIVATE /W4)
    target_compile_options(aoc2024 PRIVATE /W4)
endif()
# Nur für den Debug-Build Optimierungen ausschalten
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Og)
else ()
    add_compile_options(-O3)
endif()

# Include directories
target_include_directories(aoc2024_lib PUBLIC include)

# Link libraries
target_link_libraries(aoc2024_lib ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(aoc2024 aoc2024_lib)

# Copy input files to the build directory so they're accessible when running
add_custom_command(TARGET aoc2024 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/inputs
    $<TARGET_FILE_DIR:aoc2024>/inputs
    COMMENT "Copying input files to build directory")

# Add tests if GoogleTest is available
if(EXISTS "${CMAKE_SOURCE_DIR}/tests/CMakeLists.txt")
    add_subdirectory(tests)
endif()