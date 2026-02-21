/**
 * @file string_utils.cpp
 * @brief Implementation of string manipulation utilities
 */

#include "utils/string_utils.hpp"

#include <algorithm>
#include <cctype>

namespace aoc::utils {

std::vector<std::string> split(const std::string& str, const char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        if (!token.empty()) {
            tokens.push_back(token);
        }
    }

    return tokens;
}

std::string trim(const std::string& str) {
    const size_t start = str.find_first_not_of(" \t\n\r\f\v");

    if (start == std::string::npos) {
        return "";
    }

    const size_t end = str.find_last_not_of(" \t\n\r\f\v");

    return str.substr(start, end - start + 1);
}

bool starts_with(const std::string& str, const std::string& prefix) {
    if (prefix.length() > str.length()) {
        return false;
    }

    return std::equal(prefix.begin(), prefix.end(), str.begin());
}

bool ends_with(const std::string& str, const std::string& suffix) {
    if (suffix.length() > str.length()) {
        return false;
    }

    return std::equal(suffix.rbegin(), suffix.rend(), str.rbegin());
}

int to_int(const std::string& str) {
    return std::stoi(trim(str));
}

long long to_ll(const std::string& str) {
    return std::stoll(trim(str));
}

} // namespace aoc::utils