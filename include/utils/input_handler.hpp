#pragma once

/**
 * @file input_handler.hpp
 * @brief Utilities for reading puzzle input files
 *
 * Provides functions to read input files either as a vector of lines
 * or as a single raw string.
 */

#include <string>
#include <vector>

namespace aoc::utils {

/**
 * @brief Reads input from a file and returns it as a vector of strings
 *
 * Each line in the file becomes one element in the returned vector.
 * Empty lines are preserved.
 *
 * @param filepath Path to the input file
 * @return Vector of strings, each representing a line from the input file
 * @throws std::runtime_error if the file cannot be opened
 */
[[nodiscard]] std::vector<std::string> read_input(const std::string& filepath);

/**
 * @brief Reads input from a file and returns it as a single string
 *
 * The entire file content is returned as-is, including newlines.
 *
 * @param filepath Path to the input file
 * @return String containing the entire file content
 * @throws std::runtime_error if the file cannot be opened
 */
[[nodiscard]] std::string read_input_raw(const std::string& filepath);

} // namespace aoc::utils