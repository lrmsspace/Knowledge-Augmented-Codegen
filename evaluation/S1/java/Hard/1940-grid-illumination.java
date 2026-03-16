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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] gridIllumination(int n, int[][] lamps, int[][] queries) {
        Map<Integer, Integer> rowMap = new HashMap<>();
        Map<Integer, Integer> colMap = new HashMap<>();
        Map<Integer, Integer> diagMap = new HashMap<>();
        Map<Integer, Integer> antiDiagMap = new HashMap<>();
        Set<Long> lampSet = new HashSet<>();

        for (int[] lamp : lamps) {
            int r = lamp[0];
            int c = lamp[1];
            long code = ((long) r << 32) | c;
            if (lampSet.add(code)) {
                rowMap.put(r, rowMap.getOrDefault(r, 0) + 1);
                colMap.put(c, colMap.getOrDefault(c, 0) + 1);
                diagMap.put(r - c, diagMap.getOrDefault(r - c, 0) + 1);
                antiDiagMap.put(r + c, antiDiagMap.getOrDefault(r + c, 0) + 1);
            }
        }

        int[] result = new int[queries.length];
        int[][] directions = {
            {0, 0}, {0, 1}, {0, -1},
            {1, 0}, {1, 1}, {1, -1},
            {-1, 0}, {-1, 1}, {-1, -1}
        };

        for (int i = 0; i < queries.length; i++) {
            int r = queries[i][0];
            int c = queries[i][1];

            if (rowMap.getOrDefault(r, 0) > 0 ||
                colMap.getOrDefault(c, 0) > 0 ||
                diagMap.getOrDefault(r - c, 0) > 0 ||
                antiDiagMap.getOrDefault(r + c, 0) > 0) {
                result[i] = 1;
            } else {
                result[i] = 0;
            }

            for (int[] dir : directions) {
                int nr = r + dir[0];
                int nc = c + dir[1];
                long code = ((long) nr << 32) | nc;
                if (lampSet.remove(code)) {
                    rowMap.put(nr, rowMap.get(nr) - 1);
                    colMap.put(nc, colMap.get(nc) - 1);
                    diagMap.put(nr - nc, diagMap.get(nr - nc) - 1);
                    antiDiagMap.put(nr + nc, antiDiagMap.get(nr + nc) - 1);
                }
            }
        }

        return result;
    }
}
