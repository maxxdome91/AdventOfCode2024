#pragma once

/**
 * @file string_utils.hpp
 * @brief String manipulation utilities for puzzle solving
 *
 * Provides common string operations like splitting, trimming,
 * and type conversions.
 */

#include <sstream>
#include <string>
#include <vector>

namespace aoc::utils {

/**
 * @brief Splits a string by a delimiter
 *
 * Empty tokens are skipped in the result.
 *
 * @param str The string to split
 * @param delimiter The character to split on
 * @return Vector of non-empty strings containing the split parts
 */
[[nodiscard]] std::vector<std::string> split(const std::string& str, char delimiter);

/**
 * @brief Trims whitespace from both ends of a string
 *
 * Removes spaces, tabs, newlines, carriage returns, form feeds,
 * and vertical tabs from the beginning and end.
 *
 * @param str The string to trim
 * @return The trimmed string
 */
[[nodiscard]] std::string trim(const std::string& str);

/**
 * @brief Checks if a string starts with a prefix
 *
 * @param str The string to check
 * @param prefix The prefix to look for
 * @return true if the string starts with the prefix, false otherwise
 */
[[nodiscard]] bool starts_with(const std::string& str, const std::string& prefix);

/**
 * @brief Checks if a string ends with a suffix
 *
 * @param str The string to check
 * @param suffix The suffix to look for
 * @return true if the string ends with the suffix, false otherwise
 */
[[nodiscard]] bool ends_with(const std::string& str, const std::string& suffix);

/**
 * @brief Converts a string to an integer
 *
 * Automatically trims whitespace before conversion.
 *
 * @param str The string to convert
 * @return The integer value
 * @throws std::invalid_argument if conversion fails
 * @throws std::out_of_range if value is out of int range
 */
[[nodiscard]] int to_int(const std::string& str);

/**
 * @brief Converts a string to a long long
 *
 * Automatically trims whitespace before conversion.
 *
 * @param str The string to convert
 * @return The long long value
 * @throws std::invalid_argument if conversion fails
 * @throws std::out_of_range if value is out of long long range
 */
[[nodiscard]] long long to_ll(const std::string& str);

} // namespace aoc::utils