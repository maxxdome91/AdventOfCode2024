/**
 * @file day10.cpp
 * @brief Implementation of Day 10: Hoof It
 * 
 * Puzzle Summary:
 * - We are given a topographic map of heights (0-9).
 * - A hiking trail starts at 0, ends at 9, and increases by exactly 1 at each step.
 * - Movement is only up, down, left, or right (no diagonals).
 * - Part 1 (Score): Count how many unique 9-height positions are reachable from each trailhead (0).
 * - Part 2 (Rating): Count the total number of distinct hiking trails starting from each trailhead (0).
 * - Goal: Calculate the sum of scores (Part 1) and the sum of ratings (Part 2).
 */

#include "days/day10.hpp"

#include <ranges>
#include <vector>
#include <string>
#include <set>

namespace aoc::day10
{
    /**
     * @brief Recommended helper to check if a coordinate is within grid bounds.
     */
    bool is_valid(int r, int c, int rows, int cols)
    {
        return r >= 0 && c >= 0 && r < rows && c < cols;
    }

    /**
     * @brief Recommended helper for Part 1: Find all unique 9s reachable from a position.
     * @tip Use a std::set<std::pair<int, int>> to store coordinates of reached 9s to ensure uniqueness.
     */
    void find_reachable_nines(int r, int c, const std::vector<std::vector<int>>& grid,
                              std::set<std::pair<int, int>>& found_nines)
    {
        auto current_height = grid[r][c];

        // 1. Base case: If current height is 9, add coordinates to set and return.
        if (current_height == 9)
        {
            found_nines.insert({r, c});
            return;
        }

        // 2. Explore 4 cardinal neighbors (Up, Down, Left, Right).
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        // 3. Move only if neighbor is valid AND neighbor_height == current_height + 1.
        for (int i = 0; i < 4; ++i)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (is_valid(nr, nc, grid.size(), grid[0].size()) && grid[nr][nc] == current_height + 1)
            {
                find_reachable_nines(nr, nc, grid, found_nines);
            }
        }
    }

    /**
     * @brief Recommended helper for Part 2: Count all distinct paths to any 9.
     * @return The number of distinct paths starting from (r, c).
     * @tip This can be implemented with recursion. Memoization (caching results for a cell)
     *      could improve performance, though it may not be strictly necessary for this grid size.
     */
    int count_distinct_paths(int r, int c, const std::vector<std::vector<int>>& grid,
                             std::vector<std::vector<int>>& memo)
    {
        if (memo[r][c] != -1)
        {
            return memo[r][c];
        }
        // TODO: Implement recursive path counting
        // 1. Base case: If current height is 9, return 1 (one path found).
        auto current_height = grid[r][c];

        // 1. Base case: If current height is 9, add coordinates to set and return.
        if (current_height == 9)
        {
            return 1;
        }
        // 2. Initialize path count to 0.
        auto path_count = 0;
        // 3. For each valid neighbor with height + 1, add its count_distinct_paths to total.
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (is_valid(nr, nc, grid.size(), grid[0].size()) && grid[nr][nc] == current_height + 1)
            {
                path_count += count_distinct_paths(nr, nc, grid, memo);
            }
        }
        // 4. Return total.
        memo[r][c] = path_count;
        return path_count;
    }

    std::string solve_part1(const std::vector<std::string>& input)
    {
        auto result = 0;
        std::vector<std::vector<int>> grid;
        grid.reserve(input.size());
        for (const auto& line : input)
        {
            std::vector<int> row;
            row.reserve(line.size());
            for (char c : line)
            {
                row.push_back(c - '0');
            }
            grid.push_back(std::move(row));
        }
        for (size_t r = 0; r < grid.size(); ++r)
        {
            for (size_t c = 0; c < grid[r].size(); ++c)
            {
                int digit = grid[r][c];
                if (digit == 0)
                {
                    std::set<std::pair<int, int>> found_nines;
                    find_reachable_nines(static_cast<int>(r), static_cast<int>(c), grid, found_nines);
                    result += found_nines.size();
                }
            }
        }
        return std::to_string(result);
    }

    std::string solve_part2(const std::vector<std::string>& input)
    {
        auto result = 0;
        std::vector<std::vector<int>> grid;
        grid.reserve(input.size());
        for (const auto& line : input)
        {
            std::vector<int> row;
            row.reserve(line.size());
            for (char c : line)
            {
                row.push_back(c - '0');
            }
            grid.push_back(std::move(row));
        }
        std::vector<std::vector<int>> memo(grid.size(), std::vector<int>(grid[0].size(), -1));
        for (size_t r = 0; r < grid.size(); ++r)
        {
            for (size_t c = 0; c < grid[r].size(); ++c)
            {
                int digit = grid[r][c];
                if (digit == 0)
                {
                    result += count_distinct_paths(static_cast<int>(r), static_cast<int>(c), grid, memo);
                }
            }
        }
        return std::to_string(result);
    }
} // namespace aoc::day10
