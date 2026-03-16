// Source: https://leetcode.com/problems/paint-house-iv/   |   Difficulty: Medium
//
// Problem Description:
// You are given an even integer n representing the number of houses arranged in a straight line, and a 2D array cost of size n x 3, where cost[i][j] represents the cost of painting house i with color j + 1.
//
// The houses will look beautiful if they satisfy the following conditions:
//
//
// 	No two adjacent houses are painted the same color.
// 	Houses equidistant from the ends of the row are not painted the same color. For example, if n = 6, houses at positions (0, 5), (1, 4), and (2, 3) are considered equidistant.
//
//
// Return the minimum cost to paint the houses such that they look beautiful.
//
// Example:
// Input: n = 4, cost = [[3,5,7],[6,2,9],[4,8,1],[7,3,5]]
//
// Output: 9
//
// Explanation:
//
// The optimal painting sequence is [1, 2, 3, 2] with corresponding costs [3, 2, 1, 3]. This satisfies the following conditions:
//
//
// 	No adjacent houses have the same color.
// 	Houses at positions 0 and 3 (equidistant from the ends) are not painted the same color (1 != 2).
// 	Houses at positions 1 and 2 (equidistant from the ends) are not painted the same color (2 != 3).
//
//
// The minimum cost to paint the houses so that they look beautiful is 3 + 2 + 1 + 3 = 9.
//
// Constraints:
// 2 <= n <= 105
// 	n is even.
// 	cost.length == n
// 	cost[i].length == 3
// 	0 <= cost[i][j] <= 105
//
// Helpful references (internal KB):
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long minCost(int n, vector<vector<int>>& cost) {
        const int COLORS = 3;
        // dp[i][c]: min cost to paint up to house i with color c
        vector<vector<long long>> dp(n, vector<long long>(COLORS, LLONG_MAX));

        // Base case: first house
        for (int c = 0; c < COLORS; ++c) {
            dp[0][c] = cost[0][c];
        }

        // Fill dp table
        for (int i = 1; i < n; ++i) {
            for (int c = 0; c < COLORS; ++c) {
                for (int pc = 0; pc < COLORS; ++pc) {
                    if (c != pc && c != (COLORS - 1 - pc)) { // adjacent and equidistant constraints
                        dp[i][c] = min(dp[i][c], dp[i - 1][pc] + cost[i][c]);
                    }
                }
            }
        }

        // Find the minimum cost for the last house
        long long result = LLONG_MAX;
        for (int c = 0; c < COLORS; ++c) {
            result = min(result, dp[n - 1][c]);
        }

        return result;          
    }
};
