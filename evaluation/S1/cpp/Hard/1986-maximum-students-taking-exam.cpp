// Source: https://leetcode.com/problems/maximum-students-taking-exam/   |   Difficulty: Hard
//
// Problem Description:
// Given a m * n matrix seats  that represent seats distributions in a classroom. If a seat is broken, it is denoted by '#' character otherwise it is denoted by a '.' character.
//
// Students can see the answers of those sitting next to the left, right, upper left and upper right, but he cannot see the answers of the student sitting directly in front or behind him. Return the maximum number of students that can take the exam together without any cheating being possible.
//
// Students must be placed in seats in good condition.
//
// Example:
// Input: seats = [["#",".","#","#",".","#"],
//                 [".","#","#","#","#","."],
//                 ["#",".","#","#",".","#"]]
// Output: 4
// Explanation: Teacher can place 4 students in available seats so they don't cheat on the exam.
//
// Constraints:
// seats contains only characters '.' and'#'.
// 	m == seats.length
// 	n == seats[i].length
// 	1 <= m <= 8
// 	1 <= n <= 8
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxStudents(vector<vector<char>>& seats) {
        int m = seats.size();
        int n = seats[0].size();
        vector<int> dp(1 << n, -1);
        dp[0] = 0;

        for (int i = 0; i < m; ++i) {
            vector<int> ndp(1 << n, -1);
            for (int mask = 0; mask < (1 << n); ++mask) {
                if (dp[mask] == -1) continue;
                for (int nmask = 0; nmask < (1 << n); ++nmask) {
                    bool valid = true;
                    for (int j = 0; j < n; ++j) {
                        if ((nmask & (1 << j)) != 0) {
                            if (seats[i][j] == '#') {
                                valid = false;
                                break;
                            }
                            if (j > 0 && (nmask & (1 << (j - 1))) != 0) {
                                valid = false;
                                break;
                            }
                            if (j + 1 < n && (nmask & (1 << (j + 1))) != 0) {
                                valid = false;
                                break;
                            }
                            if (j > 0 && (mask & (1 << (j - 1))) != 0) {
                                valid = false;
                                break;
                            }
                            if (j + 1 < n && (mask & (1 << (j + 1))) != 0) {
                                valid = false;
                                break;
                            }
                        }
                    }
                    if (valid) {
                        int count = __builtin_popcount(nmask);
                        ndp[nmask] = max(ndp[nmask], dp[mask] + count);
                    }
                }
            }
            dp = move(ndp);
        }

        int result = 0;
        for (int val : dp) {
            result = max(result, val);
        }
        return result;          
    }
};
