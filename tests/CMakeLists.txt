# tests/CMakeLists.txt
cmake_minimum_required(VERSION 3.20)
project(Aoc2024Tests)

# Find GoogleTest
find_package(GTest REQUIRED)

# Create test executable
add_executable(aoc2024_tests
    test_main.cpp
    test_utils.cpp
    test_days.cpp
)

# Define the project root directory as a compile-time constant
# This allows tests to find input files regardless of working directory
target_compile_definitions(aoc2024_tests PRIVATE
    AOC_PROJECT_ROOT="${CMAKE_SOURCE_DIR}"
)

# Link libraries
target_link_libraries(aoc2024_tests
    GTest::gtest
    aoc2024_lib  # Link against our main library
)

# Include directories
target_include_directories(aoc2024_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Enable testing
enable_testing()
add_test(NAME Aoc2024Tests COMMAND aoc2024_tests)