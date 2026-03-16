// Source: https://leetcode.com/problems/minimum-time-to-break-locks-i/   |   Difficulty: Medium
//
// Problem Description:
// Bob is stuck in a dungeon and must break n locks, each requiring some amount of energy to break. The required energy for each lock is stored in an array called strength where strength[i] indicates the energy needed to break the ith lock.
//
// To break a lock, Bob uses a sword with the following characteristics:
//
//
// 	The initial energy of the sword is 0.
// 	The initial factor x by which the energy of the sword increases is 1.
// 	Every minute, the energy of the sword increases by the current factor x.
// 	To break the ith lock, the energy of the sword must reach at least strength[i].
// 	After breaking a lock, the energy of the sword resets to 0, and the factor x increases by a given value k.
//
//
// Your task is to determine the minimum time in minutes required for Bob to break all n locks and escape the dungeon.
//
// Return the minimum time required for Bob to break all n locks.
//
// Example:
// Input: strength = [3,4,1], k = 1
//
// Output: 4
//
// Explanation:
//
//
// 	
// 		
// 			Time
// 			Energy
// 			x
// 			Action
// 			Updated x
// 		
// 		
// 			0
// 			0
// 			1
// 			Nothing
// 			1
// 		
// 		
// 			1
// 			1
// 			1
// 			Break 3rd Lock
// 			2
// 		
// 		
// 			2
// 			2
// 			2
// 			Nothing
// 			2
// 		
// 		
// 			3
// 			4
// 			2
// 			Break 2nd Lock
// 			3
// 		
// 		
// 			4
// 			3
// 			3
// 			Break 1st Lock
// 			3
// 		
// 	
//
//
// The locks cannot be broken in less than 4 minutes; thus, the answer is 4.
//
// Constraints:
// n == strength.length
// 	1 <= n <= 8
// 	1 <= K <= 10
// 	1 <= strength[i] <= 106
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
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
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} strength
 * @param {number} k
 * @return {number}
 */
var findMinimumTime = function(strength, k) {
    const n = strength.length;
    const dp = new Array(1 << n).fill(Infinity);
    dp[0] = 0;

    for (let mask = 0; mask < (1 << n); mask++) {
        let maxTimeForCurrentMask = 0;
        for (let i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                const timeToBreakLock = Math.ceil(strength[i] / (dp[mask ^ (1 << i)] + 1));
                maxTimeForCurrentMask = Math.max(maxTimeForCurrentMask, timeToBreakLock);
            }
        }
        dp[mask] = maxTimeForCurrentMask;
        if (mask !== 0) {
            dp[mask] += k * countSetBits(mask);
        }
    }

    return dp[(1 << n) - 1];
};
