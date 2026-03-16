// Source: https://leetcode.com/problems/painting-the-walls/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed integer arrays, cost and time, of size n representing the costs and the time taken to paint n different walls respectively. There are two painters available:
//
//
// 	A paid painter that paints the ith wall in time[i] units of time and takes cost[i] units of money.
// 	A free painter that paints any wall in 1 unit of time at a cost of 0. But the free painter can only be used if the paid painter is already occupied.
//
//
// Return the minimum amount of money required to paint the n walls.
//
// Example:
// Input: cost = [1,2,3,2], time = [1,2,3,2]
// Output: 3
// Explanation: The walls at index 0 and 1 will be painted by the paid painter, and it will take 3 units of time; meanwhile, the free painter will paint the walls at index 2 and 3, free of cost in 2 units of time. Thus, the total cost is 1 + 2 = 3.
//
// Constraints:
// 1 <= cost.length <= 500
// 	cost.length == time.length
// 	1 <= cost[i] <= 106
// 	1 <= time[i] <= 500
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Range Minimum Query (array, sparse-table)
//   • When to use: When performing many range minimum queries on a static array, especially when query time needs to be logarithmic after initial preprocessing.
//   • Idea: A data structure that precomputes minimums for all possible ranges of power-of-two lengths, allowing O(1) query time after O(N log N) preprocessing. It efficiently answers range minimum queries on an immutable array.
//   • Invariants: For any `j`, `dp[i][j]` stores the minimum value in the segment starting at `i` with length `2^j`.; The `log_table[k]` stores `floor(log2(k))` for efficient length calculation.
//   • Tips: Precompute log values or use `std::log2` for efficient length calculations.; The `dp[i][j]` entry stores the minimum in the range `[i, i + 2^j - 1]`.
//   • Pitfalls: Does not support updates to the array elements; it's for static data only.; Higher memory consumption compared to some other range query structures.
// - Introduction to Dynamic Programming (array, dp-1d)
//   • When to use: When a problem can be broken down into smaller, overlapping subproblems and an optimal solution to the larger problem can be constructed from optimal solutions to its subproblems. It's suitable for optimizing recursive solutions with repeated computations.
//   • Idea: Dynamic Programming (DP) solves complex problems by breaking them into simpler overlapping subproblems and storing the results to avoid redundant computations. It typically achieves polynomial time complexity, often O(N) or O(N^2) for 1D DP, by trading space for time.
//   • Invariants: dp[i] stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been correctly computed before dp[i] is calculated.
//   • Tips: Clearly define the DP state and its meaning.; Identify the base cases for the recurrence relation.
//   • Pitfalls: Incorrectly defining the DP state or recurrence relation.; Missing or incorrect base cases leading to infinite recursion or wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} cost
 * @param {number[]} time
 * @return {number}
 */
var paintWalls = function(cost, time) {
    const n = cost.length;
    const dp = new Array(n + 1).fill(Infinity);
    dp[0] = 0;
    for (let i = 1; i <= n; i++) {
        for (let j = 0; j < i; j++) {
            const paidTime = time[i - 1];
            const freeTime = i - j - 1;
            if (paidTime > freeTime) {
                dp[i] = Math.min(dp[i], dp[j] + cost[i - 1]);
            } else {
                dp[i] = Math.min(dp[i], dp[j]);
            }
        }
            
    }
    return dp[n];   
    
};
