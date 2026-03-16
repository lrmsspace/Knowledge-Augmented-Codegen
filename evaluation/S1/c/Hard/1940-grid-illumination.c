// Source: https://leetcode.com/problems/grid-illumination/   |   Difficulty: Hard
//
// Problem Description:
// There is a 2D grid of size n x n where each cell of this grid has a lamp that is initially turned off.
//
// You are given a 2D array of lamp positions lamps, where lamps[i] = [rowi, coli] indicates that the lamp at grid[rowi][coli] is turned on. Even if the same lamp is listed more than once, it is turned on.
//
// When a lamp is turned on, it illuminates its cell and all other cells in the same row, column, or diagonal.
//
// You are also given another 2D array queries, where queries[j] = [rowj, colj]. For the jth query, determine whether grid[rowj][colj] is illuminated or not. After answering the jth query, turn off the lamp at grid[rowj][colj] and its 8 adjacent lamps if they exist. A lamp is adjacent if its cell shares either a side or corner with grid[rowj][colj].
//
// Return an array of integers ans, where ans[j] should be 1 if the cell in the jth query was illuminated, or 0 if the lamp was not.
//
// Example:
// Input: n = 5, lamps = [[0,0],[4,4]], queries = [[1,1],[1,0]]
// Output: [1,0]
// Explanation: We have the initial grid with all lamps turned off. In the above picture we see the grid after turning on the lamp at grid[0][0] then turning on the lamp at grid[4][4].
// The 0th query asks if the lamp at grid[1][1] is illuminated or not (the blue square). It is illuminated, so set ans[0] = 1. Then, we turn off all lamps in the red square.
//
// The 1st query asks if the lamp at grid[1][0] is illuminated or not (the blue square). It is not illuminated, so set ans[1] = 0. Then, we turn off all lamps in the red rectangle.
//
// Constraints:
// 1 <= n <= 109
// 	0 <= lamps.length <= 20000
// 	0 <= queries.length <= 20000
// 	lamps[i].length == 2
// 	0 <= rowi, coli < n
// 	queries[j].length == 2
// 	0 <= rowj, colj < n
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Hash Tables (array, hashing, enumeration)
//   • When to use: Use hash tables when efficient storage and retrieval of data by a key are required. They are ideal for implementing dictionaries, sets, or caches where average O(1) time complexity for operations is crucial.
//   • Idea: Hash tables store key-value pairs by mapping keys to array indices using a hash function and a collision resolution strategy. They provide average O(1) time complexity for insertion, deletion, and lookup operations.
//   • Invariants: Each key, if present, is stored at an index derived from its hash code.; If key1.equals(key2), their hash codes produce the same array index (before collision resolution).
//   • Tips: Design hash functions to distribute keys uniformly across the table.; Ensure hashCode() and equals() methods are consistent for custom objects.
//   • Pitfalls: Poor hash functions lead to excessive collisions and O(N) worst-case performance.; Inconsistent hashCode() and equals() can cause data retrieval failures.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
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
int* gridIllumination(int n, int** lamps, int lampsSize, int* lampsColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    // Hash map entry structure
    typedef struct LampInfo {
        int count;
    } LampInfo;

    // Hash map sizes
    #define HASH_MAP_SIZE 40011

    // Hash maps for rows, columns, diagonals, and anti-diagonals
    LampInfo* rowMap[HASH_MAP_SIZE] = {0};
    LampInfo* colMap[HASH_MAP_SIZE] = {0};
    LampInfo* diagMap[HASH_MAP_SIZE] = {0};
    LampInfo* antiDiagMap[HASH_MAP_SIZE] = {0};

    // Hash function for integers
    unsigned long long hashInt(int key) {
        return ((unsigned long long)key * 2654435761u) % HASH_MAP_SIZE;
    }

    // Function to increment lamp count in the hash map
    void incrementLampCount(LampInfo** map, int key) {
        unsigned long long hashIndex = hashInt(key);
        LampInfo* entry = map[hashIndex];
        while (entry && entry->count != key) {
            hashIndex = (hashIndex + 1) % HASH_MAP_SIZE;
            entry = map[hashIndex];
        }
        if (!entry) {
            entry = (LampInfo*)malloc(sizeof(LampInfo));
            entry->count = 0;
            map[hashIndex] = entry;
        }
        entry->count++;
    }

    // Populate the hash maps with lamp information
    for (int i = 0; i < lampsSize; i++) {
        int r = lamps[i][0];
        int c = lamps[i][1];
        incrementLampCount(rowMap, r);
        incrementLampCount(colMap, c);
        incrementLampCount(diagMap, r - c);
        incrementLampCount(antiDiagMap, r + c);
    }

    // Prepare result array
    int* result = (int*)malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;

    // Process each query
    for (int i = 0; i < queriesSize; i++) {
        int r = queries[i][0];
        int c = queries[i][1];
        unsigned long long rowHash = hashInt(r);
        unsigned long long colHash = hashInt(c);
        unsigned long long diagHash = hashInt(r - c);
        unsigned long long antiDiagHash = hashInt(r + c);

        // Check if the cell is illuminated
        LampInfo* rowEntry = rowMap[rowHash];
        LampInfo* colEntry = colMap[colHash];
        LampInfo* diagEntry = diagMap[diagHash];
        LampInfo* antiDiagEntry = antiDiagMap[antiDiagHash];

        if ((rowEntry && rowEntry->count > 0) ||
            (colEntry && colEntry->count > 0) ||
            (diagEntry && diagEntry->count > 0) ||
            (antiDiagEntry && antiDiagEntry->count > 0)) {
            result[i] = 1; // Illuminated
        } else {
            result[i] = 0; // Not illuminated
        }

        // Turn off the lamp at (r, c) and its adjacent lamps
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                int nr = r + dr;
                int nc = c + dc;
                if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                    unsigned long long nrHash = hashInt(nr);
                    unsigned long long ncHash = hashInt(nc);
                    unsigned long long ndiagHash = hashInt(nr - nc);
                    unsigned long long nantiDiagHash = hashInt(nr + nc);

                    LampInfo* nRowEntry = rowMap[nrHash];
                    LampInfo* nColEntry = colMap[ncHash];
                    LampInfo* nDiagEntry = diagMap[ndiagHash];
                    LampInfo* nAntiDiagEntry = antiDiagMap[nantiDiagHash];

                    if (nRowEntry && nRowEntry->count > 0) nRowEntry->count--;
                    if (nColEntry && nColEntry->count > 0) nColEntry->count--;
                    if (nDiagEntry && nDiagEntry->count > 0) nDiagEntry->count--;
                    if (nAntiDiagEntry && nAntiDiagEntry->count > 0) nAntiDiagEntry->count--;
                }
            }
        }
    }
    // Free allocated memory for hash maps
    for (int i = 0; i < HASH_MAP_SIZE; i++) {
        if (rowMap[i]) free(rowMap[i]);
        if (colMap[i]) free(colMap[i]);
        if (diagMap[i]) free(diagMap[i]);
        if (antiDiagMap[i]) free(antiDiagMap[i]);
    }   
    return result;
}
