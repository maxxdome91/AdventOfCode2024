/**
 * @file input_handler.cpp
 * @brief Implementation of input file handling utilities
 */

#include "utils/input_handler.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace aoc::utils {

std::vector<std::string> read_input(const std::string& filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filepath);
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    return lines;
}

std::string read_input_raw(const std::string& filepath) {
    std::ifstream file(filepath);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filepath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

} // namespace aoc::utils