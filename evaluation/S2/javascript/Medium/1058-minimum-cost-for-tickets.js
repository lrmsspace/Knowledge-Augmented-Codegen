// Source: https://leetcode.com/problems/minimum-cost-for-tickets/   |   Difficulty: Medium
//
// Problem Description:
// You have planned some train traveling one year in advance. The days of the year in which you will travel are given as an integer array days. Each day is an integer from 1 to 365.
//
// Train tickets are sold in three different ways:
//
//
// 	a 1-day pass is sold for costs[0] dollars,
// 	a 7-day pass is sold for costs[1] dollars, and
// 	a 30-day pass is sold for costs[2] dollars.
//
//
// The passes allow that many days of consecutive travel.
//
//
// 	For example, if we get a 7-day pass on day 2, then we can travel for 7 days: 2, 3, 4, 5, 6, 7, and 8.
//
//
// Return the minimum number of dollars you need to travel every day in the given list of days.
//
// Example:
// Input: days = [1,4,6,7,8,20], costs = [2,7,15]
// Output: 11
// Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
// On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
// On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
// On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
// In total, you spent $11 and covered all the days of your travel.
//
// Constraints:
// 1 <= days.length <= 365
// 	1 <= days[i] <= 365
// 	days is in strictly increasing order.
// 	costs.length == 3
// 	1 <= costs[i] <= 1000
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} days
 * @param {number[]} costs
 * @return {number}
 */
var mincostTickets = function(days, costs) {
    const daySet = new Set(days);
    const lastDay = days[days.length - 1];
    const dp = new Array(lastDay + 1).fill(0);
    for (let i = 1; i <= lastDay; i++) {
        if (!daySet.has(i)) {
            dp[i] = dp[i - 1];
        } else {
            dp[i] = Math.min(
                dp[Math.max(0, i - 1)] + costs[0],
                dp[Math.max(0, i - 7)] + costs[1],
                dp[Math.max(0, i - 30)] + costs[2]
            );
        }
    }
    return dp[lastDay];
};
