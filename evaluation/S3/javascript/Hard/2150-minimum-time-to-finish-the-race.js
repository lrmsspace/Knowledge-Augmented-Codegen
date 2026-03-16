// Source: https://leetcode.com/problems/minimum-time-to-finish-the-race/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array tires where tires[i] = [fi, ri] indicates that the ith tire can finish its xth successive lap in fi * ri(x-1) seconds.
//
//
// 	For example, if fi = 3 and ri = 2, then the tire would finish its 1st lap in 3 seconds, its 2nd lap in 3 * 2 = 6 seconds, its 3rd lap in 3 * 22 = 12 seconds, etc.
//
//
// You are also given an integer changeTime and an integer numLaps.
//
// The race consists of numLaps laps and you may start the race with any tire. You have an unlimited supply of each tire and after every lap, you may change to any given tire (including the current tire type) if you wait changeTime seconds.
//
// Return the minimum time to finish the race.
//
// Example:
// Input: tires = [[2,3],[3,4]], changeTime = 5, numLaps = 4
// Output: 21
// Explanation: 
// Lap 1: Start with tire 0 and finish the lap in 2 seconds.
// Lap 2: Continue with tire 0 and finish the lap in 2 * 3 = 6 seconds.
// Lap 3: Change tires to a new tire 0 for 5 seconds and then finish the lap in another 2 seconds.
// Lap 4: Continue with tire 0 and finish the lap in 2 * 3 = 6 seconds.
// Total time = 2 + 6 + 5 + 2 + 6 = 21 seconds.
// The minimum time to complete the race is 21 seconds.
//
// Constraints:
// 1 <= tires.length <= 105
// 	tires[i].length == 2
// 	1 <= fi, changeTime <= 105
// 	2 <= ri <= 105
// 	1 <= numLaps <= 1000
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when performing many range queries on a static array where the query operation is idempotent (e.g., min, max, GCD) to achieve O(1) query time after O(N log N) precomputation.
//   • Idea: A data structure that precomputes answers for all possible range queries of power-of-two lengths, allowing O(1) query time for idempotent operations like range minimum/maximum queries. Precomputation takes O(N log N) time and space.
//   • Invariants: The `st[k][i]` entry stores the result of the operation for the range `[i, i + 2^k - 1]`.; All ranges of length `2^k` starting at `i` are correctly computed in `st[k][i]` during precomputation.
//   • Tips: Precompute logarithms for O(1) lookup of `floor(log2(length))` during queries.; Sparse tables are most efficient for idempotent operations (min, max, GCD, OR, AND) due to overlapping segments.
//   • Pitfalls: Not suitable for dynamic arrays or scenarios requiring updates, as modifications invalidate the precomputed table.; High memory usage: requires O(N log N) space, which can be significant for large N.
// - Sparse Table (array, sparse-table, dp-2d)
//   • When to use: Use when you need to answer range queries, especially Range Minimum/Maximum Queries, on an immutable array very quickly. It is ideal for scenarios where the data does not change and query performance is critical.
//   • Idea: Sparse Table is a data structure that precomputes answers for all range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like Range Minimum/Maximum Queries on a static array, with O(N log N) precomputation.
//   • Invariants: st[k][i] holds the result for the segment starting at index i with length 2^k.; For any k > 0, st[k][i] combines the results of two adjacent segments of length 2^(k-1).
//   • Tips: Precompute log2 values to find the largest power of two in O(1).; Best suited for idempotent operations like minimum, maximum, or GCD.
//   • Pitfalls: Does not support array updates; any modification invalidates the structure.; Inefficient for non-idempotent operations like range sum or XOR in O(1).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} tires
 * @param {number} changeTime
 * @param {number} numLaps
 * @return {number}
 */
var minimumFinishTime = function(tires, changeTime, numLaps) {
    const maxLaps = Math.min(numLaps, 20); // Limit to 20 laps to prevent overflow
    const dp = new Array(maxLaps + 1).fill(Infinity);
    dp[0] = 0;
        
    for (let i = 1; i <= maxLaps; i++) {
        for (let [f, r] of tires) {
            if (f * Math.pow(r, i - 1) > changeTime + f) break; // Optimization: if current tire is more expensive than changing + first lap, skip
            dp[i] = Math.min(dp[i], dp[i - 1] + f * Math.pow(r, i - 1));
        }
    }
    return dp[numLaps];
}   
    