// Source: https://leetcode.com/problems/minimum-score-by-changing-two-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums.
//
//
// 	The low score of nums is the minimum absolute difference between any two integers.
// 	The high score of nums is the maximum absolute difference between any two integers.
// 	The score of nums is the sum of the high and low scores.
//
//
// Return the minimum score after changing two elements of nums.
//
// Example:
// Input: nums = [1,4,7,8,5]
//
// Output: 3
//
// Explanation:
//
//
// 	Change nums[0] and nums[1] to be 6 so that nums becomes [6,6,7,8,5].
// 	The low score is the minimum absolute difference: |6 - 6| = 0.
// 	The high score is the maximum absolute difference: |8 - 5| = 3.
// 	The sum of high and low score is 3.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
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
var minimizeSum = function(nums) {
    nums.sort((a, b) => a - b);
    const n = nums.length;
    
    // There are 3 cases to consider:
    // 1. Change the two smallest elements: new low = nums[2] - nums[0], new high = nums[n-1] - nums[2]
    // 2. Change the two largest elements: new low = nums[n-1] - nums[n-3], new high = nums[n-3] - nums[0]
    // 3. Change the smallest and largest elements: new low = nums[n-2] - nums[1], new high = nums[n-2] - nums[1]
    
    const case1 = (nums[n-1] - nums[2]) + (nums[2] - nums[0]);
    const case2 = (nums[n-3] - nums[0]) + (nums[n-1] - nums[n-3]);
    const case3 = (nums[n-2] - nums[1]) + (nums[n-2] - nums[1]);
    
    return Math.min(case1, case2, case3);
};
