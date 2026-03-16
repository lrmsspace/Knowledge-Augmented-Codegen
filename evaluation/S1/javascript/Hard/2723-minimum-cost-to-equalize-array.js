// Source: https://leetcode.com/problems/minimum-cost-to-equalize-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and two integers cost1 and cost2. You are allowed to perform either of the following operations any number of times:
//
//
// 	Choose an index i from nums and increase nums[i] by 1 for a cost of cost1.
// 	Choose two different indices i, j, from nums and increase nums[i] and nums[j] by 1 for a cost of cost2.
//
//
// Return the minimum cost required to make all elements in the array equal. 
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [4,1], cost1 = 5, cost2 = 2
//
// Output: 15
//
// Explanation: 
//
// The following operations can be performed to make the values equal:
//
//
// 	Increase nums[1] by 1 for a cost of 5. nums becomes [4,2].
// 	Increase nums[1] by 1 for a cost of 5. nums becomes [4,3].
// 	Increase nums[1] by 1 for a cost of 5. nums becomes [4,4].
//
//
// The total cost is 15.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	1 <= cost1 <= 106
// 	1 <= cost2 <= 106
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Ternary Search (number, binary-search)
//   • When to use: Use when searching for the minimum or maximum of a unimodal function over a continuous interval. It efficiently narrows down the search space by evaluating the function at two internal points.
//   • Idea: Ternary search is an optimization algorithm for finding the extremum (minimum or maximum) of a unimodal function within a given interval. It repeatedly reduces the search interval by two-thirds, achieving logarithmic time complexity with respect to the interval size.
//   • Invariants: The global extremum of the unimodal function within the initial range is always contained within the current interval [L, R].; The interval [L, R] is non-empty and its length strictly decreases in each iteration.
//   • Tips: Carefully define the search interval [L, R] for the function.; Choose two internal points, typically L + (R-L)/3 and R - (R-L)/3.
//   • Pitfalls: Applying to non-unimodal functions yields incorrect results.; Floating-point precision issues can lead to infinite loops or incorrect bounds.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} cost1
 * @param {number} cost2
 * @return {number}
 */
var minCostToEqualizeArray = function(nums, cost1, cost2) {
    const n = nums.length;
    const totalCost = nums.reduce((acc, num) => acc + num, 0);
    const target = Math.floor(totalCost / n);

    let cost = 0;
    for (let i = 0; i < n; i++) {
        if (nums[i] < target) {
            cost += (target - nums[i]) * cost1;
        } else if (nums[i] > target) {
            cost += (nums[i] - target) * cost2;
        }
    }

    return cost;
};
