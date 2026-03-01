/**
 * @file day09.cpp
 * @brief Implementation of Day 9: Disk Fragmenter
 *
 * ============================================================================
 * PUZZLE SUMMARY
 * ============================================================================
 *
 * The input is a "disk map" - a single line of digits representing alternating
 * file lengths and free space lengths. Files are assigned IDs sequentially.
 *
 * Example: "2333133121414131402" represents:
 *   - File 0: 2 blocks
 *   - Free: 3 blocks
 *   - File 1: 3 blocks
 *   - Free: 3 blocks
 *   - File 2: 1 block
 *   - ... and so on
 *
 * Visualized: 00...111...2...333.44.5555.6666.777.888899
 *
 * ============================================================================
 * PART 1: BLOCK-BY-BLOCK COMPACTION
 * ============================================================================
 *
 * Move individual blocks from the end of the disk to the leftmost free space.
 * Continue until there are no gaps between file blocks.
 *
 * Algorithm (Two-Pointer Approach):
 * 1. Parse the disk map into a flat array of blocks
 * 2. Initialize left pointer at start (looking for free space)
 * 3. Initialize right pointer at end (looking for file blocks)
 * 4. While left < right:
 *    a. Move left pointer to next free space
 *    b. Move right pointer to previous file block
 *    c. If both found and left < right, swap them
 * 5. Calculate checksum
 *
 * Time Complexity: O(n) where n is the total number of blocks
 * Space Complexity: O(n) for the disk array
 *
 * ============================================================================
 * PART 2: WHOLE-FILE COMPACTION
 * ============================================================================
 *
 * Move entire files (not individual blocks) to the leftmost free span that
 * can fit them. Process files in descending order by ID (highest ID first).
 * Files can only move LEFT, never right.
 *
 * Algorithm:
 * 1. Parse disk into file spans and free spans
 * 2. For each file (from highest ID to lowest):
 *    a. Find the leftmost free span that:
 *       - Has length >= file length
 *       - Is positioned BEFORE the file's current position
 *    b. If found, move the file there and update free spans
 * 3. Calculate checksum
 *
 * Time Complexity: O(f * s) where f = number of files, s = number of free spans
 *                  (Can be optimized with better data structures)
 * Space Complexity: O(n) for tracking spans
 *
 * ============================================================================
 * IMPLEMENTATION TIPS
 * ============================================================================
 *
 * DATA STRUCTURES:
 * - For Part 1: std::vector<int> where -1 = free space, 0+ = file ID
 * - For Part 2: Two vectors of Span structs (files and free spaces)
 *
 * EDGE CASES TO WATCH:
 * - Empty input or single character input
 * - Disk map ending with free space (no trailing file)
 * - Files that cannot be moved (no suitable free span)
 * - Checksum overflow (use long long / int64_t)
 * - Files at position 0 (checksum contribution is 0)
 *
 * STANDARD LIBRARY MODULES TO CONSIDER:
 * - <vector>: For disk representation
 * - <algorithm>: For std::find_if, std::sort, etc.
 * - <cstdint>: For int64_t to handle large checksums
 */

#include "days/day09.hpp"

#include <algorithm>
#include <cstdint>
#include <numeric>
#include <string>
#include <vector>

namespace aoc::day09
{
    // ============================================================================
    // HELPER FUNCTION IMPLEMENTATIONS
    // ============================================================================

    [[nodiscard]] std::vector<int> parse_disk_map(const std::string& disk_map)
    {
        // HINT: Iterate through each character in disk_map
        // - Even indices (0, 2, 4, ...) are file lengths
        // - Odd indices (1, 3, 5, ...) are free space lengths
        // - Convert char digit to int: int length = disk_map[i] - '0'
        // - Track file_id starting at 0, incrementing for each file
        //
        // Example: "12345" -> [0, -1, -1, 1, 1, 1, -1, -1, -1, -1, 2, 2, 2, 2, 2]
        //          (0 is file ID, -1 is free space)

        const auto total_blocks = std::accumulate(
            disk_map.begin(), disk_map.end(), 0,
            [](int sum, char c) { return sum + (c - '0'); }
        );

        std::vector<int> disk;
        disk.reserve(total_blocks);
        int file_index = 0;
        for (size_t i = 0; i < disk_map.size(); ++i)
        {
            char c = disk_map[i];
            if (i % 2 == 0)
            {
                for (int j = 0; j < (c - '0'); ++j)
                {
                    disk.emplace_back(file_index);
                }
                ++file_index;
            }
            else
            {
                for (int j = 0; j < (c - '0'); ++j)
                {
                    disk.emplace_back(-1);
                }
            }
        }
        return disk;
    }

    [[nodiscard]] long long calculate_checksum(const std::vector<int>& disk)
    {
        // HINT: Iterate through the disk with index
        // For each position i:
        //   if disk[i] is a file block (not free space):
        //     checksum += i * disk[i]
        //
        // IMPORTANT: Use long long for checksum to avoid overflow!
        // The input can be ~20,000 characters, resulting in many blocks.

        long long checksum = 0;
        for (size_t i = 0; i < disk.size(); ++i)
        {
            int b = disk[i];
            if (b != -1)
            {
                checksum += i * b;
            }
        }
        return checksum;
    }

    [[nodiscard]] int find_first_free_space(const std::vector<int>& disk, int start_index)
    {
        // HINT: Linear search from start_index forward
        // Return the index of the first free space block
        // Return -1 if no free space found
        //
        // Consider: What value represents free space in your representation?

        // Your implementation here...
        auto it = std::ranges::find_if(disk.begin() + start_index, disk.end(), [](int d)
        {
            return d == -1;
        });
        return it != disk.end() ? static_cast<int>(std::distance(disk.begin(), it)) : -1;
    }

    [[nodiscard]] int find_last_file_block(const std::vector<int>& disk, int start_index)
    {
        // HINT: Linear search from start_index backward
        // Return the index of the last file block
        // Return -1 if no file block found
        //
        // Consider: What values represent file blocks in your representation?

        // Your implementation here...
        auto it = std::ranges::find_if(disk.rbegin() + (static_cast<long>(disk.size()) - 1 - start_index), disk.rend(),
                                       [](int d) { return d != -1; });
        return it != disk.rend()
                   ? (static_cast<int>(disk.size()) - 1 - static_cast<int>(std::distance(disk.rbegin(), it)))
                   : -1;
    }

    [[nodiscard]] int find_suitable_free_span(
        const std::vector<Span>& free_spans,
        int required_length,
        int max_position
    )
    {
        // HINT: Find the LEFTMOST free span that:
        // 1. Has length >= required_length
        // 2. Starts before max_position (file's current position)
        //
        // If free_spans is sorted by position, you can stop searching
        // once you find the first suitable span.
        //
        // Return the index in free_spans vector, or -1 if none found.

        // Your implementation here...
        auto it = std::ranges::find_if(free_spans, [required_length, max_position](const Span& s) -> bool
        {
            return s.length >= required_length && s.start < max_position;
        });
        return (it != free_spans.end()) ? static_cast<int>(std::distance(free_spans.begin(), it)) : -1;
    }

    void parse_into_spans(
        const std::string& disk_map,
        std::vector<Span>& file_spans,
        std::vector<Span>& free_spans
    )
    {
        // HINT: Track current position as you parse
        // For each character:
        // - Even index: It's a file, create a Span with file_id, add to file_spans
        // - Odd index: It's free space, create a Span with file_id=-1, add to free_spans
        // - Update current position by the length
        // - Increment file_id after each file
        //
        // This representation is more efficient for Part 2's whole-file moves.

        // Your implementation here...
        auto file_id = 0;
        size_t current_position = 0;
        for (size_t i = 0; i < disk_map.size(); ++i)
        {
            char c = disk_map[i];
            if (i % 2 == 0)
            {
                file_spans.emplace_back(current_position, c - '0', file_id);
                ++file_id;
                current_position += c - '0';
            } else
            {
                free_spans.emplace_back(current_position, c - '0', -1);
                current_position += c - '0';
            }
        }
    }

    // ============================================================================
    // PART 1 SOLUTION
    // ============================================================================

    std::string solve_part1(const std::vector<std::string>& input)
    {
        // TODO: Implement Part 1
        //
        // STEP-BY-STEP APPROACH:
        //
        // 1. Get the disk map from input[0] (it's a single line)
        //    - Note: input is a vector of strings, but the puzzle input is one line
        //
        // 2. Parse the disk map into a vector of blocks
        //    - Call parse_disk_map() helper function
        //
        // 3. Compact the disk using two-pointer technique:
        //    - left = 0, right = disk.size() - 1
        //    - while left < right:
        //      a. Find next free space from left
        //      b. Find next file block from right
        //      c. If both found and left < right, swap them
        //
        // 4. Calculate and return the checksum
        //    - Call calculate_checksum() helper function
        //
        // DEBUG TIP: For the example "2333133121414131402", the answer is 1928
        // You can print the disk state after each swap to verify your logic.

        // Your implementation here...
        auto disk = parse_disk_map(input[0]);
        if (disk.empty()) return "0";

        int left = 0;
        int right = static_cast<int>(disk.size()) - 1;
        while (left < right)
        {
            left = find_first_free_space(disk, left);
            right = find_last_file_block(disk, right);
            if (left != -1 && right != -1 && left < right)
            {
                std::swap(disk[left], disk[right]);
            }
        }

        return std::to_string(calculate_checksum(disk));
    }

    // ============================================================================
    // PART 2 SOLUTION
    // ============================================================================

    std::string solve_part2(const std::vector<std::string>& input)
    {
        if (input.empty() || input[0].empty()) return "0";

        const std::string& disk_map = input[0];

        // Parse into file spans and free spans
        std::vector<Span> file_spans;
        std::vector<Span> free_spans;
        parse_into_spans(disk_map, file_spans, free_spans);

        // Process files in descending order by ID
        for (int i = static_cast<int>(file_spans.size()) - 1; i >= 0; --i)
        {
            Span& file = file_spans[i];
            int old_start = file.start;

            // Find the leftmost free span that can fit this file
            int free_idx = find_suitable_free_span(free_spans, file.length, old_start);

            if (free_idx != -1)
            {
                Span& free_span = free_spans[free_idx];

                // Move the file to the free span
                file.start = free_span.start;

                // Update the free span
                free_span.length -= file.length;
                free_span.start += file.length;

                // If the free span is now empty (exactly filled), remove it
                if (free_span.length == 0)
                {
                    free_spans.erase(free_spans.begin() + free_idx);
                }

                // Add the file's old position as a new free span
                // Insert in sorted order by position
                Span old_position{old_start + file.length, file.length, -1};
                auto insert_pos = std::ranges::find_if(free_spans, [pos = old_position.start](const Span& s)
                {
                    return s.start > pos;
                });
                free_spans.insert(insert_pos, old_position);
            }
        }

        // Calculate checksum from the final file spans
        int64_t checksum = 0;
        for (const Span& file : file_spans)
        {
            for (int j = 0; j < file.length; ++j)
            {
                checksum += static_cast<int64_t>(file.start + j) * file.file_id;
            }
        }

        return std::to_string(checksum);
    }
} // namespace aoc::day09
