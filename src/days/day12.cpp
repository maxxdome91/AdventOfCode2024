/**
 * @file day12.cpp
 * @brief Implementation of Day 12: Garden Groups
 */

#include "days/day12.hpp"

#include <queue>
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <compare>

namespace aoc::day12
{
    struct Point
    {
        int r, c;
        auto operator<=>(const Point&) const = default;
    };

    struct Region
    {
        char type;
        std::vector<Point> cells;
        std::set<Point> cell_set; // Useful for quick lookups
    };

    /**
     * @brief Checks if a given point is within the grid boundaries.
     * 
     * @param p The point (r, c) to check.
     * @param grid The 2D vector of strings representing the grid.
     * @return true if the point is within the grid bounds, false otherwise.
     */
    [[nodiscard]] bool is_in_bounds(const Point& p, const std::vector<std::string>& grid)
    {
        return p.r >= 0 && p.r < static_cast<int>(grid.size()) &&
            p.c >= 0 && p.c < static_cast<int>(grid[0].size());
    }

    /**
     * @brief Uses Flood Fill (BFS/DFS) to find a contiguous region.
     *
     * Strategy:
     * 1. Start from (r, c) and find all connected cells of the same plant type.
     * 2. Mark found cells in a `visited` 2D array to avoid reprocessing.
     * 3. Store the region's plant type and all its coordinates.
     */
    Region find_region(int r, int c, const std::vector<std::string>& grid, std::vector<std::vector<bool>>& visited)
    {
        auto type = grid[r][c];
        Region result{type, {}, {}};


        std::queue<Point> queue{};
        visited[r][c] = true;
        queue.push(Point{r, c});

        int dr[4] = {-1, 0, 1, 0};
        int dc[4] = {0, 1, 0, -1};
        while (!queue.empty())
        {
            auto p = queue.front();
            queue.pop();

            result.cells.push_back(p);
            result.cell_set.insert(p);

            for (int i = 0; i < 4; ++i)
            {
                Point next{p.r + dr[i], p.c + dc[i]};
                if (is_in_bounds(next, grid) && grid[next.r][next.c] == type && !visited[next.r][next.c])
                {
                    visited[next.r][next.c] = true;
                    queue.push(next);
                }
            }
        }
        return result;
    }

    /**
     * @brief Part 1: Perimeter Calculation.
     *
     * Strategy:
     * - For each cell in the region, check its 4 cardinal neighbors.
     * - If a neighbor is outside the grid OR has a different plant type
     *   (not in this region's cell_set), increment the perimeter count.
     */
    long long calculate_perimeter(const Region& region, const std::vector<std::string>& grid)
    {
        long long result = 0;
        int dr[4] = {-1, 0, 1, 0};
        int dc[4] = {0, 1, 0, -1};

        for (const auto& p : region.cells)
        {
            for (int i = 0; i < 4; ++i)
            {
                Point next{p.r + dr[i], p.c + dc[i]};
                if (!is_in_bounds(next, grid) || !region.cell_set.contains(next))
                {
                    result++;
                }
            }
        }
        return result;
    }

    /**
     * @brief Part 2: Number of Sides (equivalent to number of corners).
     *
     * Strategy:
     * - A region has as many sides as it has corners (outer and inner).
     * - For each cell, we check its 4 potential corners (NW, NE, SW, SE).
     * - An EXTERNAL corner exists if both cardinal neighbors are NOT in the region.
     * - An INTERNAL corner exists if both cardinal neighbors ARE in the region
     *   BUT the diagonal neighbor is NOT.
     */
    long long count_corners(const Region& region, const std::vector<std::string>& grid)
    {
        long long result = 0;
        for (const auto& p : region.cells)
        {
            auto is_in = [&](int r, int c)
            {
                return region.cell_set.contains({r, c});
            };

            //Top-left corner
            bool n = is_in(p.r - 1, p.c);
            bool w = is_in(p.r, p.c - 1);
            bool nw = is_in(p.r - 1, p.c - 1);
            if ((!n && !w) || (n && w && !nw)) result++;

            // Top-Right Corner
            bool e = is_in(p.r, p.c + 1);
            bool ne = is_in(p.r - 1, p.c + 1);
            if ((!n && !e) || (n && e && !ne)) result++;

            // Bottom-Left Corner
            bool s = is_in(p.r + 1, p.c);
            bool sw = is_in(p.r + 1, p.c - 1);
            if ((!s && !w) || (s && w && !sw)) result++;

            // Bottom-Right Corner
            bool se = is_in(p.r + 1, p.c + 1);
            if ((!s && !e) || (s && e && !se)) result++;
        }
        return result;
    }

    /**
     * @brief Main logic for both parts.
     *
     * 1. Initialize `total_price = 0` and a `visited` 2D array.
     * 2. Iterate through every cell (r, c) in the grid:
     *    a. If (r, c) is already visited, skip.
     *    b. Else, call find_region() to get the new Region.
     *    c. Calculate Area (region.cells.size()) and Perimeter/Corners.
     *    d. Add (Area * Metric) to total_price.
     */
    std::string solve_part1(const std::vector<std::string>& input)
    {
        long long result = 0;
        std::vector<std::vector<bool>> visited(input.size(), std::vector<bool>(input[0].size(), false));
        for (size_t r = 0; r < input.size(); ++r)
        {
            const auto& line = input[r];
            for (size_t c = 0; c < line.size(); ++c)
            {
                if (visited[r][c])
                {
                    continue;
                }
                auto region = find_region(static_cast<int>(r), static_cast<int>(c), input, visited);
                auto perimeter = calculate_perimeter(region, input);
                result += region.cells.size() * perimeter;
            }
        }
        return std::to_string(result);
    }

    std::string solve_part2(const std::vector<std::string>& input)
    {
        long long result = 0;
        std::vector<std::vector<bool>> visited(input.size(), std::vector<bool>(input[0].size(), false));
        for (size_t r = 0; r < input.size(); ++r)
        {
            const auto& line = input[r];
            for (size_t c = 0; c < line.size(); ++c)
            {
                if (visited[r][c])
                {
                    continue;
                }
                auto region = find_region(static_cast<int>(r), static_cast<int>(c), input, visited);
                auto corners = count_corners(region, input);
                result += region.cells.size() * corners;
            }
        }
        return std::to_string(result);
    }
} // namespace aoc::day12
