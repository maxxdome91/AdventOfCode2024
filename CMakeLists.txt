cmake_minimum_required(VERSION 3.20)
project(AdventOfCode2024 LANGUAGES CXX)

# Require C++23 with GCC (needed for std::views::enumerate)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Require GCC compiler (for full C++23 ranges support including std::views::enumerate)
if(NOT CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(FATAL_ERROR 
        "GCC is required for full C++23 ranges support (std::views::enumerate).\n"
        "Current compiler: ${CMAKE_CXX_COMPILER_ID}\n"
        "Please set CMAKE_CXX_COMPILER to g++-15 or use:\n"
        "  -DCMAKE_CXX_COMPILER=/opt/homebrew/bin/g++-15"
    )
endif()

if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 15.0)
    message(FATAL_ERROR 
        "GCC 15 or newer is required for std::views::enumerate.\n"
        "Current version: ${CMAKE_CXX_COMPILER_VERSION}\n"
        "Please install GCC 15+ via Homebrew: brew install gcc"
    )
endif()

message(STATUS "Using GCC ${CMAKE_CXX_COMPILER_VERSION} at ${CMAKE_CXX_COMPILER}")

# Include directories
include_directories(include)

# Find packages
find_package(Threads REQUIRED)

# Enable compile commands for LSP/intellisense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Option to build tests (default: OFF to avoid GTest ABI issues)
option(BUILD_TESTS "Build GoogleTest tests" OFF)

# Source files
file(GLOB_RECURSE LIBRARY_SOURCES 
    "src/*.cpp"
    "src/utils/*.cpp"
    "src/days/*.cpp"
)

# Exclude main.cpp from library sources
list(FILTER LIBRARY_SOURCES EXCLUDE REGEX "main\\.cpp$")

# Create a library with the common code
add_library(aoc2024_lib STATIC ${LIBRARY_SOURCES})

# Create the main executable
add_executable(aoc2024 main.cpp)

# Compiler warnings
target_compile_options(aoc2024_lib PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(aoc2024 PRIVATE -Wall -Wextra -Wpedantic)

# Optimization flags based on build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(aoc2024_lib PRIVATE -Og -g)
    target_compile_options(aoc2024 PRIVATE -Og -g)
else()
    target_compile_options(aoc2024_lib PRIVATE -O3)
    target_compile_options(aoc2024 PRIVATE -O3)
endif()

# Include directories
target_include_directories(aoc2024_lib PUBLIC include)

# Link libraries
target_link_libraries(aoc2024_lib PUBLIC ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(aoc2024 PRIVATE aoc2024_lib)

# Copy input files to the build directory
add_custom_command(TARGET aoc2024 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/inputs
    $<TARGET_FILE_DIR:aoc2024>/inputs
    COMMENT "Copying input files to build directory"
)

# Build tests if enabled
if(BUILD_TESTS)
    if(EXISTS "${CMAKE_SOURCE_DIR}/tests/CMakeLists.txt")
        add_subdirectory(tests)
    else()
        message(WARNING "BUILD_TESTS is ON but tests/CMakeLists.txt not found")
    endif()
endif()
