/**
 * @file day09.hpp
 * @brief Day 9: Disk Fragmenter
 *
 * PUZZLE CONTEXT:
 * ===============
 * This puzzle simulates disk fragmentation/compaction. The input is a "disk map" - a single
 * line of digits where alternating positions represent:
 *   - Positions 0, 2, 4, ... (even indices): Length of a file
 *   - Positions 1, 3, 5, ... (odd indices): Length of free space
 *
 * Each file gets an ID number based on its order of appearance (0, 1, 2, ...).
 * The disk can be visualized as a sequence of blocks where:
 *   - Digits represent file IDs (file blocks)
 *   - '.' represents free space blocks
 *
 * Example: "12345" represents: 0..111....22222
 *          (1 block of file 0, 2 free, 3 blocks of file 1, 4 free, 5 blocks of file 2)
 *
 * Part 1: Move individual blocks one at a time from the end to the leftmost free space.
 *         Calculate checksum: sum of (position * file_id) for all file blocks.
 *
 * Part 2: Move whole files (not individual blocks) to the leftmost span of free space
 *         that can fit the entire file. Process files in descending order by ID.
 *         Calculate the same checksum.
 */

#pragma once

#include <string>
#include <vector>

namespace aoc::day09 {

/**
 * @brief Solves part 1: Block-by-block compaction
 * @param input Vector of strings representing the puzzle input (single line of digits)
 * @return String representation of the filesystem checksum
 *
 * ALGORITHM STRATEGY:
 * 1. Parse the disk map into a representation of the disk (array of blocks)
 * 2. Use two pointers: one from left finding free space, one from right finding file blocks
 * 3. Swap blocks until pointers meet
 * 4. Calculate checksum by iterating through the compacted disk
 */
[[nodiscard]] std::string solve_part1(const std::vector<std::string>& input);

/**
 * @brief Solves part 2: Whole-file compaction
 * @param input Vector of strings representing the puzzle input (single line of digits)
 * @return String representation of the filesystem checksum
 *
 * ALGORITHM STRATEGY:
 * 1. Parse the disk map, tracking file positions and free space spans
 * 2. Process files from highest ID to lowest
 * 3. For each file, find the leftmost free span that can fit it entirely
 * 4. If found, move the whole file to that span
 * 5. Calculate checksum on the final arrangement
 */
[[nodiscard]] std::string solve_part2(const std::vector<std::string>& input);

// ============================================================================
// RECOMMENDED HELPER FUNCTIONS (implement these yourself)
// ============================================================================

/**
 * @brief Parses the disk map string into a block representation
 *
 * HINT: Consider using a vector where:
 *   - Positive values represent file IDs
 *   - A sentinel value (e.g., -1) represents free space
 *
 * ALGORITHM:
 * - Iterate through the input string character by character
 * - Even indices (0, 2, 4, ...) represent file lengths
 * - Odd indices (1, 3, 5, ...) represent free space lengths
 * - Track file IDs incrementally as you encounter files
 *
 * @param disk_map The input string of digits
 * @return Vector representing each block on disk
 */
[[nodiscard]] std::vector<int> parse_disk_map(const std::string& disk_map);

/**
 * @brief Calculates the filesystem checksum
 *
 * HINT: The checksum is the sum of (position * file_id) for each file block.
 * Free space blocks are skipped (not multiplied by anything).
 *
 * EDGE CASE: Make sure to only sum positions that contain actual file blocks,
 * not free space markers.
 *
 * @param disk Vector representing the disk blocks
 * @return The calculated checksum (use long long to avoid overflow!)
 */
[[nodiscard]] long long calculate_checksum(const std::vector<int>& disk);

/**
 * @brief Finds the index of the leftmost free space block at or after start_index
 *
 * HINT: Useful for the two-pointer approach in Part 1.
 * Consider what value represents "free space" in your disk representation.
 *
 * @param disk Vector representing the disk blocks
 * @param start_index Where to start searching from
 * @return Index of first free space, or -1 if none found
 */
[[nodiscard]] int find_first_free_space(const std::vector<int>& disk, int start_index);

/**
 * @brief Finds the index of the rightmost file block at or before start_index
 *
 * HINT: Useful for the two-pointer approach in Part 1.
 * Search backwards from the end of the disk.
 *
 * @param disk Vector representing the disk blocks
 * @param start_index Where to start searching from (searching backwards)
 * @return Index of last file block, or -1 if none found
 */
[[nodiscard]] int find_last_file_block(const std::vector<int>& disk, int start_index);

/**
 * @brief Represents a contiguous span on the disk
 *
 * HINT: Useful for Part 2 where you need to track free space spans
 * and file spans separately. This allows you to move entire files
 * rather than individual blocks.
 */
struct Span {
    int start;      // Starting index of the span
    int length;     // Number of blocks in the span
    int file_id;    // File ID (-1 for free space spans)
};

/**
 * @brief Finds a free span that can fit a file of given size, to the left of max_position
 *
 * HINT: For Part 2, you need to find the LEFTMOST free span that is
 * large enough to hold the entire file. The span must be to the LEFT
 * of the file's current position (we only move files left, not right).
 *
 * DATA STRUCTURE TIP: Consider maintaining a list of free spans sorted by position.
 * This makes finding the leftmost suitable span efficient.
 *
 * @param free_spans List of free space spans (sorted by position)
 * @param required_length Minimum length needed
 * @param max_position The file's current start position (don't move right!)
 * @return Index of suitable span in the list, or -1 if none found
 */
[[nodiscard]] int find_suitable_free_span(
    const std::vector<Span>& free_spans,
    int required_length,
    int max_position
);

/**
 * @brief Alternative approach: Parse disk into file spans and free spans
 *
 * HINT: For Part 2, instead of a flat array of blocks, consider tracking:
 * - A list of file spans (with their IDs, positions, and lengths)
 * - A list of free space spans (with positions and lengths)
 *
 * This makes it easier to move whole files and update free space.
 *
 * @param disk_map The input string of digits
 * @param file_spans Output: list of file spans
 * @param free_spans Output: list of free space spans
 */
void parse_into_spans(
    const std::string& disk_map,
    std::vector<Span>& file_spans,
    std::vector<Span>& free_spans
);

} // namespace aoc::day09
