// Source: https://leetcode.com/problems/largest-element-in-an-array-after-merge-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisting of positive integers.
//
// You can do the following operation on the array any number of times:
//
//
// 	Choose an index i such that 0 <= i < nums.length - 1 and nums[i] <= nums[i + 1]. Replace the element nums[i + 1] with nums[i] + nums[i + 1] and delete the element nums[i] from the array.
//
//
// Return the value of the largest element that you can possibly obtain in the final array.
//
// Example:
// Input: nums = [2,3,7,9,3]
// Output: 21
// Explanation: We can apply the following operations on the array:
// - Choose i = 0. The resulting array will be nums = [5,7,9,3].
// - Choose i = 1. The resulting array will be nums = [5,16,3].
// - Choose i = 0. The resulting array will be nums = [21,3].
// The largest element in the final array is 21. It can be shown that we cannot obtain a larger element.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long maxArrayValue(int[] nums) {
        long maxValue = 0;
        long currentSum = 0;

        // Traverse the array from right to left
        for (int i = nums.length - 1; i >= 0; i--) {
            // If the current number is less than or equal to the current sum,
            // we can merge it into the current sum
            if (nums[i] <= currentSum) {
                currentSum += nums[i];
            } else {
                // Otherwise, we start a new segment with the current number
                currentSum = nums[i];
            }
            // Update the maximum value found so far
            maxValue = Math.max(maxValue, currentSum);
        }

        return maxValue;            
    }
}
