/**
 * @file day04.cpp
 * @brief Implementation of Day 4: Ceres Search
 */

#include "days/day04.hpp"

#include <string>
#include <vector>
#include <iostream>

namespace aoc::day04 {
    
    namespace {
        // Direction vectors for 8 directions: {row_delta, col_delta}
        // Order: NW, N, NE, W, E, SW, S, SE
        constexpr int ROW_DELTAS[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
        constexpr int COL_DELTAS[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
        constexpr int WORD_LENGTH = 4;
        constexpr std::string_view TARGET_WORD = "XMAS";
    }

    /**
     * Helper function to check if coordinates are valid in the grid
     * @param row Row index
     * @param col Column index
     * @param total_rows Total number of rows
     * @param total_cols Total number of columns
     * @return true if coordinates are within bounds
     */
    bool isValidPosition(int row, int col, int total_rows, int total_cols) {
        return row >= 0 && row < total_rows && col >= 0 && col < total_cols;
    }

    /**
     * Part 1: Count occurrences of "XMAS" in all 8 directions
     *
     * Algorithm approach:
     * 1. For each cell in the grid, check if it contains 'X'
     * 2. If yes, try to form "XMAS" in all 8 possible directions:
     *    - Horizontal: left-to-right, right-to-left
     *    - Vertical: top-to-bottom, bottom-to-top
     *    - Diagonal: 4 diagonal directions
     * 3. Count each valid "XMAS" sequence found
     */
    std::string solve_part1(const std::vector<std::string> &input) {
        if (input.empty() || input[0].empty()) {
            return "0";
        }

        const auto rows = input.size();
        const auto cols = input[0].size();
        int count = 0;

        // Direction vectors for 8 directions: {row_delta, col_delta}
        // Order: NW, N, NE, W, E, SW, S, SE

        // Loop through each position in the grid
        // If the current position is 'X', check all 8 directions for "XMAS"
        // Use helper function to validate positions during traversal
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                if (input[row][col] == 'X') {
                    for (int dir_idx = 0; dir_idx < 8; ++dir_idx) {
                        std::string sequence{input[row][col]};
                        auto next_row = static_cast<int>(row) + ROW_DELTAS[dir_idx];
                        auto next_col = static_cast<int>(col) + COL_DELTAS[dir_idx];
                        
                        for (int char_idx = 1; char_idx < 4; ++char_idx) {
                            if (isValidPosition(next_row, next_col, static_cast<int>(rows), static_cast<int>(cols))) {
                                sequence += input[next_row][next_col];
                                next_row += ROW_DELTAS[dir_idx];
                                next_col += COL_DELTAS[dir_idx];
                            } else {
                                break;
                            }
                        }
                        
                        if (sequence == TARGET_WORD) {
                            count++;
                        }
                    }
                }
            }
        }

        return std::to_string(count);
    }

    /**
     * Part 2: Count "X-MAS" patterns
     *
     * An X-MAS pattern consists of:
     * - An 'A' in the center
     * - Two 'M' and 'S' diagonally opposite each other
     * - The pattern looks like an X formed by two MAS words
     *
     * Algorithm approach:
     * 1. Loop through the grid, looking for 'A' (not on edges)
     * 2. For each 'A', check the four diagonal neighbors
     * 3. Verify that diagonals form two MAS patterns intersecting at 'A'
     * 4. Count valid X-MAS patterns
     */
    std::string solve_part2(const std::vector<std::string> &input) {
        if (input.empty() || input[0].empty()) {
            return "0";
        }

        const auto rows = input.size();
        const auto cols = input[0].size();
        int count = 0;

        // Loop through positions that aren't on the edges (need 1-cell border)
        // For each 'A' at (center_row, center_col), check diagonal neighbors:
        // - Top-left (center_row-1, center_col-1) and bottom-right (center_row+1, center_col+1)
        // - Top-right (center_row-1, center_col+1) and bottom-left (center_row+1, center_col-1)
        // Both pairs should contain 'M' and 'S' (in any order)
        for (size_t center_row = 1; center_row < rows - 1; ++center_row) {
            for (size_t center_col = 1; center_col < cols - 1; ++center_col) {
                if (input[center_row][center_col] == 'A') {
                    char tl = input[center_row - 1][center_col - 1];  // top-left
                    char tr = input[center_row - 1][center_col + 1];  // top-right
                    char bl = input[center_row + 1][center_col - 1];  // bottom-left
                    char br = input[center_row + 1][center_col + 1];  // bottom-right
                    
                    // Check if both diagonals contain 'M' and 'S'
                    bool first_diagonal_valid = (tl == 'M' && br == 'S') || (tl == 'S' && br == 'M');
                    bool second_diagonal_valid = (tr == 'M' && bl == 'S') || (tr == 'S' && bl == 'M');
                    
                    if (first_diagonal_valid && second_diagonal_valid) {
                        count++;
                    }
                }
            }
        }

        return std::to_string(count);
    }
} // namespace aoc::day04
