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
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long[] countBlackBlocks(int m, int n, int[][] coordinates) {
        long[] result = new long[5];
        result[0] = (long)(m - 1) * (n - 1);

        Map<Long, Integer> blockCountMap = new HashMap<>();

        for (int[] coordinate : coordinates) {
            int x = coordinate[0];
            int y = coordinate[1];

            for (int dx = -1; dx <= 0; dx++) {
                for (int dy = -1; dy <= 0; dy++) {
                    int blockX = x + dx;
                    int blockY = y + dy;

                    if (blockX >= 0 && blockX < m - 1 && blockY >= 0 && blockY < n - 1) {
                        long key = ((long)blockX << 32) | (blockY & 0xffffffffL);
                        blockCountMap.put(key, blockCountMap.getOrDefault(key, 0) + 1);
                    }
                }
            }
        }

        for (int count : blockCountMap.values()) {
            result[count]++;
            result[0]--;
        }

        return result;          
    }
}
