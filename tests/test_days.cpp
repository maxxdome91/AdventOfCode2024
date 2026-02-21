/**
 * @file test_days.cpp
 * @brief Unit tests for all day solutions
 *
 * Tests verify that each day's solution produces the expected results
 * for the actual puzzle inputs.
 */

#include <gtest/gtest.h>

#include "days/day01.hpp"
#include "days/day02.hpp"
#include "days/day03.hpp"
#include "days/day04.hpp"
#include "days/day05.hpp"
#include "days/day06.hpp"
#include "days/day07.hpp"
#include "days/day08.hpp"
#include "days/day09.hpp"
#include "days/day10.hpp"
#include "days/day11.hpp"
#include "days/day12.hpp"
#include "days/day13.hpp"
#include "days/day14.hpp"
#include "days/day15.hpp"
#include "days/day16.hpp"
#include "days/day17.hpp"
#include "days/day18.hpp"
#include "days/day19.hpp"
#include "days/day20.hpp"
#include "days/day21.hpp"
#include "days/day22.hpp"
#include "days/day23.hpp"
#include "days/day24.hpp"
#include "days/day25.hpp"
#include "utils/input_handler.hpp"

#include <string>
#include <vector>

/**
 * @brief Helper function to get the absolute path to input files
 *
 * Uses AOC_PROJECT_ROOT defined at compile time in CMakeLists.txt.
 *
 * @param filename Name of the input file (e.g., "day01.txt")
 * @return Full path to the input file
 */
inline std::string get_input_path(const std::string& filename) {
    return std::string(AOC_PROJECT_ROOT) + "/inputs/" + filename;
}

// ============================================================================
// Day 1 Tests
// ============================================================================

TEST(DayTests, Day01) {
    const auto input = aoc::utils::read_input(get_input_path("day01.txt"));

    const std::string part1_result = aoc::day01::solve_part1(input);
    const std::string part2_result = aoc::day01::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 2 Tests
// ============================================================================

TEST(DayTests, Day02) {
    const auto input = aoc::utils::read_input(get_input_path("day02.txt"));

    const std::string part1_result = aoc::day02::solve_part1(input);
    const std::string part2_result = aoc::day02::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 3 Tests
// ============================================================================

TEST(DayTests, Day03) {
    const auto input = aoc::utils::read_input(get_input_path("day03.txt"));

    const std::string part1_result = aoc::day03::solve_part1(input);
    const std::string part2_result = aoc::day03::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 4 Tests
// ============================================================================

TEST(DayTests, Day04) {
    const auto input = aoc::utils::read_input(get_input_path("day04.txt"));

    const std::string part1_result = aoc::day04::solve_part1(input);
    const std::string part2_result = aoc::day04::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 5 Tests
// ============================================================================

TEST(DayTests, Day05) {
    const auto input = aoc::utils::read_input(get_input_path("day05.txt"));

    const std::string part1_result = aoc::day05::solve_part1(input);
    const std::string part2_result = aoc::day05::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 6 Tests
// ============================================================================

TEST(DayTests, Day06) {
    const auto input = aoc::utils::read_input(get_input_path("day06.txt"));

    const std::string part1_result = aoc::day06::solve_part1(input);
    const std::string part2_result = aoc::day06::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 7 Tests
// ============================================================================

TEST(DayTests, Day07) {
    const auto input = aoc::utils::read_input(get_input_path("day07.txt"));

    const std::string part1_result = aoc::day07::solve_part1(input);
    const std::string part2_result = aoc::day07::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 8 Tests
// ============================================================================

TEST(DayTests, Day08) {
    const auto input = aoc::utils::read_input(get_input_path("day08.txt"));

    const std::string part1_result = aoc::day08::solve_part1(input);
    const std::string part2_result = aoc::day08::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 9 Tests
// ============================================================================

TEST(DayTests, Day09) {
    const auto input = aoc::utils::read_input(get_input_path("day09.txt"));

    const std::string part1_result = aoc::day09::solve_part1(input);
    const std::string part2_result = aoc::day09::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 10 Tests
// ============================================================================

TEST(DayTests, Day10) {
    const auto input = aoc::utils::read_input(get_input_path("day10.txt"));

    const std::string part1_result = aoc::day10::solve_part1(input);
    const std::string part2_result = aoc::day10::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 11 Tests
// ============================================================================

TEST(DayTests, Day11) {
    const auto input = aoc::utils::read_input(get_input_path("day11.txt"));

    const std::string part1_result = aoc::day11::solve_part1(input);
    const std::string part2_result = aoc::day11::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 12 Tests
// ============================================================================

TEST(DayTests, Day12) {
    const auto input = aoc::utils::read_input(get_input_path("day12.txt"));

    const std::string part1_result = aoc::day12::solve_part1(input);
    const std::string part2_result = aoc::day12::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 13 Tests
// ============================================================================

TEST(DayTests, Day13) {
    const auto input = aoc::utils::read_input(get_input_path("day13.txt"));

    const std::string part1_result = aoc::day13::solve_part1(input);
    const std::string part2_result = aoc::day13::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 14 Tests
// ============================================================================

TEST(DayTests, Day14) {
    const auto input = aoc::utils::read_input(get_input_path("day14.txt"));

    const std::string part1_result = aoc::day14::solve_part1(input);
    const std::string part2_result = aoc::day14::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 15 Tests
// ============================================================================

TEST(DayTests, Day15) {
    const auto input = aoc::utils::read_input(get_input_path("day15.txt"));

    const std::string part1_result = aoc::day15::solve_part1(input);
    const std::string part2_result = aoc::day15::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 16 Tests
// ============================================================================

TEST(DayTests, Day16) {
    const auto input = aoc::utils::read_input(get_input_path("day16.txt"));

    const std::string part1_result = aoc::day16::solve_part1(input);
    const std::string part2_result = aoc::day16::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 17 Tests
// ============================================================================

TEST(DayTests, Day17) {
    const auto input = aoc::utils::read_input(get_input_path("day17.txt"));

    const std::string part1_result = aoc::day17::solve_part1(input);
    const std::string part2_result = aoc::day17::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 18 Tests
// ============================================================================

TEST(DayTests, Day18) {
    const auto input = aoc::utils::read_input(get_input_path("day18.txt"));

    const std::string part1_result = aoc::day18::solve_part1(input);
    const std::string part2_result = aoc::day18::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 19 Tests
// ============================================================================

TEST(DayTests, Day19) {
    const auto input = aoc::utils::read_input(get_input_path("day19.txt"));

    const std::string part1_result = aoc::day19::solve_part1(input);
    const std::string part2_result = aoc::day19::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 20 Tests
// ============================================================================

TEST(DayTests, Day20) {
    const auto input = aoc::utils::read_input(get_input_path("day20.txt"));

    const std::string part1_result = aoc::day20::solve_part1(input);
    const std::string part2_result = aoc::day20::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 21 Tests
// ============================================================================

TEST(DayTests, Day21) {
    const auto input = aoc::utils::read_input(get_input_path("day21.txt"));

    const std::string part1_result = aoc::day21::solve_part1(input);
    const std::string part2_result = aoc::day21::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 22 Tests
// ============================================================================

TEST(DayTests, Day22) {
    const auto input = aoc::utils::read_input(get_input_path("day22.txt"));

    const std::string part1_result = aoc::day22::solve_part1(input);
    const std::string part2_result = aoc::day22::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 23 Tests
// ============================================================================

TEST(DayTests, Day23) {
    const auto input = aoc::utils::read_input(get_input_path("day23.txt"));

    const std::string part1_result = aoc::day23::solve_part1(input);
    const std::string part2_result = aoc::day23::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 24 Tests
// ============================================================================

TEST(DayTests, Day24) {
    const auto input = aoc::utils::read_input(get_input_path("day24.txt"));

    const std::string part1_result = aoc::day24::solve_part1(input);
    const std::string part2_result = aoc::day24::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}

// ============================================================================
// Day 25 Tests
// ============================================================================

TEST(DayTests, Day25) {
    const auto input = aoc::utils::read_input(get_input_path("day25.txt"));

    const std::string part1_result = aoc::day25::solve_part1(input);
    const std::string part2_result = aoc::day25::solve_part2(input);

    // TODO: Replace with actual expected results once implemented
    EXPECT_EQ(part1_result, "Not implemented");
    EXPECT_EQ(part2_result, "Not implemented");
}