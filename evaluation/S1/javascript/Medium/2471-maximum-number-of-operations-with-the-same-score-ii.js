// Source: https://leetcode.com/problems/maximum-number-of-operations-with-the-same-score-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of integers called nums, you can perform any of the following operation while nums contains at least 2 elements:
//
//
// 	Choose the first two elements of nums and delete them.
// 	Choose the last two elements of nums and delete them.
// 	Choose the first and the last elements of nums and delete them.
//
//
// The score of the operation is the sum of the deleted elements.
//
// Your task is to find the maximum number of operations that can be performed, such that all operations have the same score.
//
// Return the maximum number of operations possible that satisfy the condition mentioned above.
//
// Example:
// Input: nums = [3,2,1,2,3,4]
// Output: 3
// Explanation: We perform the following operations:
// - Delete the first two elements, with score 3 + 2 = 5, nums = [1,2,3,4].
// - Delete the first and the last elements, with score 1 + 4 = 5, nums = [2,3].
// - Delete the first and the last elements, with score 2 + 3 = 5, nums = [].
// We are unable to perform any more operations as nums is empty.
//
// Constraints:
// 2 <= nums.length <= 2000
// 	1 <= nums[i] <= 1000
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
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
 * @return {number}
 */
var maxOperations = function(nums) {
    const countMap = new Map();

    // Count the occurrences of each possible score (sum of pairs)
    for (let i = 0; i < nums.length; i++) {
        for (let j = i + 1; j < nums.length; j++) {
            const score = nums[i] + nums[j];
            countMap.set(score, (countMap.get(score) || 0) + 1);
        }
    }

    // Find the maximum number of operations with the same score
    let maxOperations = 0;
    for (const count of countMap.values()) {
        maxOperations = Math.max(maxOperations, count);
    }

    return maxOperations;
};
