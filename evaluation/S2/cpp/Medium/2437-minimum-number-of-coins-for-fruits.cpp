// Source: https://leetcode.com/problems/minimum-number-of-coins-for-fruits/   |   Difficulty: Medium
//
// Problem Description:
// You are given an 0-indexed integer array prices where prices[i] denotes the number of coins needed to purchase the (i + 1)th fruit.
//
// The fruit market has the following reward for each fruit:
//
//
// 	If you purchase the (i + 1)th fruit at prices[i] coins, you can get any number of the next i fruits for free.
//
//
// Note that even if you can take fruit j for free, you can still purchase it for prices[j - 1] coins to receive its reward.
//
// Return the minimum number of coins needed to acquire all the fruits.
//
// Example:
// Input: prices = [3,1,2]
//
// Output: 4
//
// Explanation:
//
//
// 	Purchase the 1st fruit with prices[0] = 3 coins, you are allowed to take the 2nd fruit for free.
// 	Purchase the 2nd fruit with prices[1] = 1 coin, you are allowed to take the 3rd fruit for free.
// 	Take the 3rd fruit for free.
//
//
// Note that even though you could take the 2nd fruit for free as a reward of buying 1st fruit, you purchase it to receive its reward, which is more optimal.
//
// Constraints:
// 1 <= prices.length <= 1000
// 	1 <= prices[i] <= 105
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
//   • When to use: Use when calculating the area of a simple polygon given its vertices in order. It is efficient for both convex and non-convex polygons.
//   • Idea: This algorithm calculates the area of a simple polygon by summing signed trapezoidal areas formed by each edge and the x-axis, or equivalently, using the shoelace formula. It achieves an optimal O(N) time complexity, where N is the number of vertices.
//   • Invariants: Vertices are processed sequentially in their given order, forming edges.; The running sum `current_sum` accumulates the signed contribution from each edge processed so far.
//   • Tips: Ensure vertices are provided in a consistent order (clockwise or counter-clockwise).; Use a data type with sufficient range (e.g., long long or double) for intermediate sums to prevent overflow.
//   • Pitfalls: Incorrect vertex order will result in an incorrect signed area or even zero.; Integer overflow can occur if coordinates are large and sums exceed standard integer limits.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumCoins(vector<int>& prices) {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int len = 1; len <= n; ++len) {
            for (int l = 0; l + len - 1 < n; ++l) {
                int r = l + len - 1;
                dp[l][r] = prices[r] + (r > l ? dp[l][r - 1] : 0);
                for (int k = l; k < r; ++k) {
                    dp[l][r] = min(dp[l][r], dp[l][k] + (k + 1 <= r ? dp[k + 1][r] : 0));
                }
            }
        }

        return dp[0][n - 1];            
    }
};
