// Source: https://leetcode.com/problems/guess-number-higher-or-lower-ii/   |   Difficulty: Medium
//
// Problem Description:
// We are playing the Guessing Game. The game will work as follows:
//
//
// 	I pick a number between 1 and n.
// 	You guess a number.
// 	If you guess the right number, you win the game.
// 	If you guess the wrong number, then I will tell you whether the number I picked is higher or lower, and you will continue guessing.
// 	Every time you guess a wrong number x, you will pay x dollars. If you run out of money, you lose the game.
//
//
// Given a particular n, return the minimum amount of money you need to guarantee a win regardless of what number I pick.
//
// Example:
// Input: n = 10
// Output: 16
// Explanation: The winning strategy is as follows:
// - The range is [1,10]. Guess 7.
//     - If this is my number, your total is $0. Otherwise, you pay $7.
//     - If my number is higher, the range is [8,10]. Guess 9.
//         - If this is my number, your total is $7. Otherwise, you pay $9.
//         - If my number is higher, it must be 10. Guess 10. Your total is $7 + $9 = $16.
//         - If my number is lower, it must be 8. Guess 8. Your total is $7 + $9 = $16.
//     - If my number is lower, the range is [1,6]. Guess 3.
//         - If this is my number, your total is $7. Otherwise, you pay $3.
//         - If my number is higher, the range is [4,6]. Guess 5.
//             - If this is my number, your total is $7 + $3 = $10. Otherwise, you pay $5.
//             - If my number is higher, it must be 6. Guess 6. Your total is $7 + $3 + $5 = $15.
//             - If my number is lower, it must be 4. Guess 4. Your total is $7 + $3 + $5 = $15.
//         - If my number is lower, the range is [1,2]. Guess 1.
//             - If this is my number, your total is $7 + $3 = $10. Otherwise, you pay $1.
//             - If my number is higher, it must be 2. Guess 2. Your total is $7 + $3 + $1 = $11.
// The worst case in all these scenarios is that you pay $16. Hence, you only need $16 to guarantee a win.
//
// Constraints:
// 1 <= n <= 200
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
// - Range Minimum Query (array, sparse-table)
//   • When to use: When performing many range minimum queries on a static array, especially when query time needs to be logarithmic after initial preprocessing.
//   • Idea: A data structure that precomputes minimums for all possible ranges of power-of-two lengths, allowing O(1) query time after O(N log N) preprocessing. It efficiently answers range minimum queries on an immutable array.
//   • Invariants: For any `j`, `dp[i][j]` stores the minimum value in the segment starting at `i` with length `2^j`.; The `log_table[k]` stores `floor(log2(k))` for efficient length calculation.
//   • Tips: Precompute log values or use `std::log2` for efficient length calculations.; The `dp[i][j]` entry stores the minimum in the range `[i, i + 2^j - 1]`.
//   • Pitfalls: Does not support updates to the array elements; it's for static data only.; Higher memory consumption compared to some other range query structures.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));   
        for (int len = 2; len <= n; ++len) {
            for (int l = 1; l + len - 1 <= n; ++l) {
                int r = l + len - 1;
                dp[l][r] = INT_MAX;
                for (int k = l; k <= r; ++k) {
                    dp[l][r] = min(dp[l][r], k + max(dp[l][k - 1], dp[k + 1][r]));
                }
            }
        }
        return dp[1][n];
    }
};
