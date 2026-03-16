// Source: https://leetcode.com/problems/painting-a-grid-with-three-different-colors/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers m and n. Consider an m x n grid where each cell is initially white. You can paint each cell red, green, or blue. All cells must be painted.
//
// Return the number of ways to color the grid with no two adjacent cells having the same color. Since the answer can be very large, return it modulo 109 + 7.
//
// Example:
// Input: m = 1, n = 1
// Output: 3
// Explanation: The three possible colorings are shown in the image above.
//
// Constraints:
// 1 <= m <= 5
// 	1 <= n <= 1000
//
// Helpful references (internal KB):
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int colorTheGrid(int m, int n) {
        const int MOD = 1e9 + 7;

        // Generate all valid column states
        vector<int> states;
        function<void(int, int)> dfs = [&](int pos, int state) {
            if (pos == m) {
                states.push_back(state);
                return;
            }
            for (int color = 0; color < 3; ++color) {
                if (pos == 0 || ((state / static_cast<int>(pow(3, pos - 1))) % 3) != color) {
                    dfs(pos + 1, state + color * static_cast<int>(pow(3, pos)));
                }
            }
        };
        dfs(0, 0);

        // Precompute compatibility between states
        int sz = states.size();
        vector<vector<int>> compat(sz);
        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < sz; ++j) {
                bool valid = true;
                for (int k = 0; k < m; ++k) {
                    int color1 = (states[i] / static_cast<int>(pow(3, k))) % 3;
                    int color2 = (states[j] / static_cast<int>(pow(3, k))) % 3;
                    if (color1 == color2) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    compat[i].push_back(j);
                }
            }
        }

        // DP to count ways to fill the grid
        vector<long long> dp(sz, 1);
        for (int col = 1; col < n; ++col) {
            vector<long long> new_dp(sz, 0);
            for (int i = 0; i < sz; ++i) {
                for (int j : compat[i]) {
                    new_dp[j] = (new_dp[j] + dp[i]) % MOD;
                }
            }
            dp = move(new_dp);
        }

        long long result = 0;
        for (long long count : dp) {
            result = (result + count) % MOD;
        }

        return static_cast<int>(result);            
    }
};
