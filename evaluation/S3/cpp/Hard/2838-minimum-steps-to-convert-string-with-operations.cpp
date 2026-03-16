// Source: https://leetcode.com/problems/minimum-steps-to-convert-string-with-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings, word1 and word2, of equal length. You need to transform word1 into word2.
//
// For this, divide word1 into one or more contiguous substrings. For each substring substr you can perform the following operations:
//
//
//  
//  Replace: Replace the character at any one index of substr with another lowercase English letter.
//  
//  
//  Swap: Swap any two characters in substr.
//  
//  
//  Reverse Substring: Reverse substr.
//  
//
//
// Each of these counts as one operation and each character of each substring can be used in each type of operation at most once (i.e. no single index may be involved in more than one replace, one swap, or one reverse).
//
// Return the minimum number of operations required to transform word1 into word2.
//
// Example:
// Input: word1 = "abcdf", word2 = "dacbe"
//
// Output: 4
//
// Explanation:
//
// Divide word1 into "ab", "c", and "df". The operations are:
//
//
//  For the substring "ab",
//
//  
//   Perform operation of type 3 on "ab" -> "ba".
//   Perform operation of type 1 on "ba" -> "da".
//  
//  
//  For the substring "c" do no operations.
//  For the substring "df",
//  
//   Perform operation of type 1 on "df" -> "bf".
//   Perform operation of type 1 on "bf" -> "be".
//
// Constraints:
// 1 <= word1.length == word2.length <= 100
//  word1 and word2 consist only of lowercase English letters.
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minOperations(string word1, string word2) {
        int n = word1.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = (word1[i] == word2[i]) ? 0 : 1;
        }
        for (int length = 2; length <= n; ++length) {
            for (int l = 0; l <= n - length; ++l) {
                int r = l + length - 1;
                dp[l][r] = min(dp[l + 1][r], dp[l][r - 1]) + 1;
                if (word1[l] == word2[r]) {
                    dp[l][r] = min(dp[l][r], dp[l + 1][r - 1]);
                } else {
                    dp[l][r] = min(dp[l][r], dp[l + 1][r - 1] + 2);
                }
            }
        }
        return dp[0][n - 1];
    }
};
