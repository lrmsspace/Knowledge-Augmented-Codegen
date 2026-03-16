// Source: https://leetcode.com/problems/number-of-black-blocks/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers m and n representing the dimensions of a 0-indexed m x n grid.
//
// You are also given a 0-indexed 2D integer matrix coordinates, where coordinates[i] = [x, y] indicates that the cell with coordinates [x, y] is colored black. All cells in the grid that do not appear in coordinates are white.
//
// A block is defined as a 2 x 2 submatrix of the grid. More formally, a block with cell [x, y] as its top-left corner where 0 <= x < m - 1 and 0 <= y < n - 1 contains the coordinates [x, y], [x + 1, y], [x, y + 1], and [x + 1, y + 1].
//
// Return a 0-indexed integer array arr of size 5 such that arr[i] is the number of blocks that contains exactly i black cells.
//
// Example:
// Input: m = 3, n = 3, coordinates = [[0,0]]
// Output: [3,1,0,0,0]
// Explanation: The grid looks like this:
//
// There is only 1 block with one black cell, and it is the block starting with cell [0,0].
// The other 3 blocks start with cells [0,1], [1,0] and [1,1]. They all have zero black cells. 
// Thus, we return [3,1,0,0,0].
//
// Constraints:
// 2 <= m <= 105
// 	2 <= n <= 105
// 	0 <= coordinates.length <= 104
// 	coordinates[i].length == 2
// 	0 <= coordinates[i][0] < m
// 	0 <= coordinates[i][1] < n
// 	It is guaranteed that coordinates contains pairwise distinct coordinates.
//
// Helpful references (internal KB):
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* countBlackBlocks(int m, int n, int** coordinates, int coordinatesSize, int* coordinatesColSize, int* returnSize) {
    // Step 1: Create a hash set to store black cell coordinates for O(1) lookups.
    typedef struct {
        int x;
        int y;
    } Coordinate;

    typedef struct {
        Coordinate* data;
        int size;
        int capacity;
    } HashSet;

    HashSet* createHashSet(int capacity) {
        HashSet* set = (HashSet*)malloc(sizeof(HashSet));
        set->data = (Coordinate*)malloc(capacity * sizeof(Coordinate));
        set->size = 0;
        set->capacity = capacity;
        return set;
    }

    void freeHashSet(HashSet* set) {
        free(set->data);
        free(set);
    }

    int hashFunction(int x, int y, int capacity) {
        return (x * 100000 + y) % capacity; // Simple hash function
    }

    void insertHashSet(HashSet* set, int x, int y) {
        if (set->size >= set->capacity) {
            // Resize the hash set if needed
            set->capacity *= 2;
            set->data = (Coordinate*)realloc(set->data, set->capacity * sizeof(Coordinate));
        }
        set->data[set->size++] = (Coordinate){x, y};
    }

    int containsHashSet(HashSet* set, int x, int y) {
        for (int i = 0; i < set->size; i++) {
            if (set->data[i].x == x && set->data[i].y == y) {
                return 1; // Found
            }
        }
        return 0; // Not found
    }

    HashSet* blackCells = createHashSet(coordinatesSize);
    for (int i = 0; i < coordinatesSize; i++) {
        insertHashSet(blackCells, coordinates[i][0], coordinates[i][1]);
    }

    // Step 2: Initialize the result array to count blocks with 0 to 4 black cells.
    long long* result = (long long*)calloc(5, sizeof(long long));

    // Step 3: Iterate through all possible top-left corners of blocks and count black cells.
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < n - 1; j++) {       
            int blackCount = 0;
            if (containsHashSet(blackCells, i, j)) blackCount++;
            if (containsHashSet(blackCells, i + 1, j)) blackCount++;
            if (containsHashSet(blackCells, i, j + 1)) blackCount++;
            if (containsHashSet(blackCells, i + 1, j + 1)) blackCount++;
            result[blackCount]++;
        }
    }
    *returnSize = 5;
    freeHashSet(blackCells);
    return result;
}
