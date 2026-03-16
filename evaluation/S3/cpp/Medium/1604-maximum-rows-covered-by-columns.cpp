// Source: https://leetcode.com/problems/maximum-rows-covered-by-columns/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix matrix and an integer numSelect.
//
// Your goal is to select exactly numSelect distinct columns from matrix such that you cover as many rows as possible.
//
// A row is considered covered if all the 1's in that row are also part of a column that you have selected. If a row does not have any 1s, it is also considered covered.
//
// More formally, let us consider selected = {c1, c2, ...., cnumSelect} as the set of columns selected by you. A row i is covered by selected if:
//
//
// 	For each cell where matrix[i][j] == 1, the column j is in selected.
// 	Or, no cell in row i has a value of 1.
//
//
// Return the maximum number of rows that can be covered by a set of numSelect columns.
//
// Example:
// Input: matrix = [[0,0,0],[1,0,1],[0,1,1],[0,0,1]], numSelect = 2
//
// Output: 3
//
// Explanation:
//
// One possible way to cover 3 rows is shown in the diagram above.
// We choose s = {0, 2}.
// - Row 0 is covered because it has no occurrences of 1.
// - Row 1 is covered because the columns with value 1, i.e. 0 and 2 are present in s.
// - Row 2 is not covered because matrix[2][1] == 1 but 1 is not present in s.
// - Row 3 is covered because matrix[2][2] == 1 and 2 is present in s.
// Thus, we can cover three rows.
// Note that s = {1, 2} will also cover 3 rows, but it can be shown that no more than three rows can be covered.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 12
// 	matrix[i][j] is either 0 or 1.
// 	1 <= numSelect <= n
//
// Helpful references (internal KB):
// - Bit manipulation (number, enumeration, simulation)
//   • When to use: When problems involve manipulating individual bits of numbers, representing sets as bitmasks, or optimizing operations on powers of two. It is also useful for certain combinatorics and dynamic programming problems.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators. This technique is often used to optimize computations, manage boolean flags efficiently, or represent subsets, typically achieving O(1) complexity for fixed-size integers.
//   • Invariants: Each bit in the mask accurately reflects the inclusion or exclusion status of its corresponding element.; Bitwise operations maintain the integrity of unaffected bits.
//   • Tips: Use (1 << k) to create a mask with the k-th bit set.; n & (n-1) clears the least significant set bit.
//   • Pitfalls: Incorrect operator precedence can lead to subtle bugs.; Mixing signed and unsigned integers in bitwise operations can yield unexpected results.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maximumRows(vector<vector<int>>& matrix, int numSelect) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> rowMask(m, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j]) {
                    rowMask[i] |= 1 << j;
                }
            }
        }

        int maxCovered = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            if (__builtin_popcount(mask) == numSelect) {
                int covered = 0;
                for (int i = 0; i < m; ++i) {
                    if ((rowMask[i] & mask) == rowMask[i]) {
                        ++covered;
                    }
                }
                maxCovered = max(maxCovered, covered);
            }
        }

        return maxCovered;          
    }
};
