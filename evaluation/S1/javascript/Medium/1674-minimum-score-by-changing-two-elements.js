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
// - Mergesort (array, merge-sort)
//   • When to use: Use when a stable, guaranteed O(N log N) time complexity sort is required, especially for large datasets or when external sorting is beneficial. It is also suitable for linked lists where random access is inefficient.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and O(N) space complexity.
//   • Invariants: Before merging, the left subarray `a[lo...mid]` and the right subarray `a[mid+1...hi]` are sorted.; During the merge, `a[lo...k-1]` contains the `k-lo` smallest elements from `aux[lo...hi]` in sorted order.
//   • Tips: Utilize an auxiliary array for merging to maintain stability and simplify the merge logic.; Consider the bottom-up iterative implementation to avoid recursion depth limits and potentially improve cache performance.
//   • Pitfalls: Requires O(N) auxiliary space, which can be a significant concern for memory-constrained environments.; Recursive implementations can lead to stack overflow errors for extremely large input arrays.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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
    
    // Change the two smallest elements to be the same as the third smallest element.
    const option1 = (nums[2] - nums[0]) + (nums[n - 1] - nums[0]);
    
    // Change the two largest elements to be the same as the third largest element.
    const option2 = (nums[n - 1] - nums[n - 3]) + (nums[n - 1] - nums[0]);
    
    // Change the smallest and largest elements to be the same as the second smallest and second largest elements, respectively.
    const option3 = (nums[n - 2] - nums[0]) + (nums[n - 1] - nums[1]);
    
    return Math.min(option1, option2, option3);
};
