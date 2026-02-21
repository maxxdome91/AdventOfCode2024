/**
 * @file test_utils.cpp
 * @brief Unit tests for utility functions
 *
 * Tests verify the correctness of input handling, string manipulation,
 * and mathematical utility functions.
 */

#include <gtest/gtest.h>

#include "utils/input_handler.hpp"
#include "utils/math_utils.hpp"
#include "utils/string_utils.hpp"

#include <cstdio>
#include <fstream>
#include <string>
#include <vector>

// ============================================================================
// Input Handler Tests
// ============================================================================

TEST(InputHandlerTest, ReadInputFile) {
    // Create a temporary input file for testing
    std::ofstream temp_file("temp_test_input.txt");
    temp_file << "line1\nline2\nline3";
    temp_file.close();

    const auto result = aoc::utils::read_input("temp_test_input.txt");

    EXPECT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "line1");
    EXPECT_EQ(result[1], "line2");
    EXPECT_EQ(result[2], "line3");

    // Clean up
    std::remove("temp_test_input.txt");
}

TEST(InputHandlerTest, ReadInputRaw) {
    // Create a temporary input file for testing
    std::ofstream temp_file("temp_test_input_raw.txt");
    temp_file << "test\ncontent\nhere";
    temp_file.close();

    const auto result = aoc::utils::read_input_raw("temp_test_input_raw.txt");

    EXPECT_EQ(result, "test\ncontent\nhere");

    // Clean up
    std::remove("temp_test_input_raw.txt");
}

// ============================================================================
// String Utilities Tests
// ============================================================================

TEST(StringUtilsTest, Split) {
    const std::string input = "a,b,c,d";
    const auto result = aoc::utils::split(input, ',');

    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "b");
    EXPECT_EQ(result[2], "c");
    EXPECT_EQ(result[3], "d");
}

TEST(StringUtilsTest, Trim) {
    EXPECT_EQ(aoc::utils::trim("  hello  "), "hello");
    EXPECT_EQ(aoc::utils::trim("\t\nhello\n\t"), "hello");
    EXPECT_EQ(aoc::utils::trim("hello"), "hello");
}

TEST(StringUtilsTest, StartsWith) {
    EXPECT_TRUE(aoc::utils::starts_with("hello world", "hello"));
    EXPECT_FALSE(aoc::utils::starts_with("hello world", "world"));
    EXPECT_TRUE(aoc::utils::starts_with("test", "te"));
    EXPECT_FALSE(aoc::utils::starts_with("test", "st"));
}

TEST(StringUtilsTest, EndsWith) {
    EXPECT_TRUE(aoc::utils::ends_with("hello world", "world"));
    EXPECT_FALSE(aoc::utils::ends_with("hello world", "hello"));
    EXPECT_TRUE(aoc::utils::ends_with("test", "st"));
    EXPECT_FALSE(aoc::utils::ends_with("test", "te"));
}

TEST(StringUtilsTest, ToInt) {
    EXPECT_EQ(aoc::utils::to_int("123"), 123);
    EXPECT_EQ(aoc::utils::to_int("  456  "), 456);
    EXPECT_EQ(aoc::utils::to_int("-789"), -789);
}

TEST(StringUtilsTest, ToLL) {
    EXPECT_EQ(aoc::utils::to_ll("1234567890123456789"), 1234567890123456789LL);
    EXPECT_EQ(aoc::utils::to_ll("  9223372036854775807  "), 9223372036854775807LL);
}

// ============================================================================
// Math Utilities Tests
// ============================================================================

TEST(MathUtilsTest, GCD) {
    EXPECT_EQ(aoc::utils::gcd(12, 8), 4);
    EXPECT_EQ(aoc::utils::gcd(17, 13), 1);
    EXPECT_EQ(aoc::utils::gcd(100, 25), 25);
}

TEST(MathUtilsTest, LCM) {
    EXPECT_EQ(aoc::utils::lcm(12, 8), 24);
    EXPECT_EQ(aoc::utils::lcm(17, 13), 221);
    EXPECT_EQ(aoc::utils::lcm(10, 15), 30);
}

TEST(MathUtilsTest, GCDMultiple) {
    std::vector<long long> nums = {12, 18, 24};
    EXPECT_EQ(aoc::utils::gcd_multiple(nums), 6);

    nums = {15, 25, 35};
    EXPECT_EQ(aoc::utils::gcd_multiple(nums), 5);
}

TEST(MathUtilsTest, LCMMultiple) {
    std::vector<long long> nums = {4, 6};
    EXPECT_EQ(aoc::utils::lcm_multiple(nums), 12);

    nums = {4, 6, 8};
    EXPECT_EQ(aoc::utils::lcm_multiple(nums), 24);
}

TEST(MathUtilsTest, AbsDiff) {
    EXPECT_EQ(aoc::utils::abs_diff(10, 5), 5);
    EXPECT_EQ(aoc::utils::abs_diff(5, 10), 5);
    EXPECT_EQ(aoc::utils::abs_diff(-5, 5), 10);
}

TEST(MathUtilsTest, Sum) {
    const std::vector<int> nums = {1, 2, 3, 4, 5};
    EXPECT_EQ(aoc::utils::sum(nums), 15);

    const std::vector<long long> nums2 = {10LL, 20LL, 30LL};
    EXPECT_EQ(aoc::utils::sum(nums2), 60LL);
}

TEST(MathUtilsTest, MinMax) {
    const std::vector<int> nums = {3, 1, 4, 1, 5, 9, 2, 6};
    EXPECT_EQ(aoc::utils::min(nums), 1);
    EXPECT_EQ(aoc::utils::max(nums), 9);
}