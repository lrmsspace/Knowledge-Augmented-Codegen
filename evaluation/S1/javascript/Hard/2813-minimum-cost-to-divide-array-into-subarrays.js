// Source: https://leetcode.com/problems/minimum-cost-to-divide-array-into-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integer arrays, nums and cost, of the same size, and an integer k.
//
// You can divide nums into subarrays. The cost of the ith subarray consisting of elements nums[l..r] is:
//
//
// 	(nums[0] + nums[1] + ... + nums[r] + k * i) * (cost[l] + cost[l + 1] + ... + cost[r]).
//
//
// Note that i represents the order of the subarray: 1 for the first subarray, 2 for the second, and so on.
//
// Return the minimum total cost possible from any valid division.
//
// Example:
// Input: nums = [3,1,4], cost = [4,6,6], k = 1
//
// Output: 110
//
// Explanation:
// The minimum total cost possible can be achieved by dividing nums into subarrays [3, 1] and [4].
//
//
// 	The cost of the first subarray [3,1] is (3 + 1 + 1 * 1) * (4 + 6) = 50.
// 	The cost of the second subarray [4] is (3 + 1 + 4 + 1 * 2) * 6 = 60.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	cost.length == nums.length
// 	1 <= nums[i], cost[i] <= 1000
// 	1 <= k <= 1000
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Convex hull trick and Li Chao tree (array, number, dp-1d)
//   • When to use: Use when the optimal solution for a subproblem depends only on solutions to smaller, contiguous subproblems. It's effective for optimizing sequential decision-making or finding optimal values in arrays.
//   • Idea: Dynamic Programming 1D solves problems by breaking them into overlapping subproblems and storing results to avoid recomputation. It typically achieves O(N) or O(N log N) time and O(N) or O(1) space complexity.
//   • Invariants: dp[i] correctly stores the optimal solution for the subproblem ending at index i.; All dp[j] for j < i have been computed and are correct.
//   • Tips: Clearly define the state: what does dp[i] represent for the subproblem?; Establish correct base cases for the smallest subproblems.
//   • Pitfalls: Incorrectly defining the state or recurrence relation.; Missing or incorrect base cases, leading to incorrect results.
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
 * @param {number[]} nums
 * @param {number[]} cost
 * @param {number} k
 * @return {number}
 */
var minimumCost = function(nums, cost, k) {
     const n = nums.length;
    const prefixNums = Array(n + 1).fill(0);
    const prefixCost = Array(n + 1).fill(0);
    for (let i = 0; i < n; i++) {
        prefixNums[i + 1] = prefixNums[i] + nums[i];
        prefixCost[i + 1] = prefixCost[i] + cost[i];
    }

    const dp = Array(n + 1).fill(Infinity);
    dp[0] = 0;

    for (let i = 1; i <= n; i++) {
        for (let j = 0; j < i; j++) {
            dp[i] = Math.min(dp[i], dp[j] + (prefixNums[i] - prefixNums[j] + k * (dp[j] === 0 ? 1 : dp[j] / (prefixCost[i] - prefixCost[j]))) * (prefixCost[i] - prefixCost[j]));
        }
    }

    return dp[n];
};
