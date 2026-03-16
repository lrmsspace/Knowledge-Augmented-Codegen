// Source: https://leetcode.com/problems/rearrange-array-elements-by-sign/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of even length consisting of an equal number of positive and negative integers.
//
// You should return the array of nums such that the the array follows the given conditions:
//
//
// 	Every consecutive pair of integers have opposite signs.
// 	For all integers with the same sign, the order in which they were present in nums is preserved.
// 	The rearranged array begins with a positive integer.
//
//
// Return the modified array after rearranging the elements to satisfy the aforementioned conditions.
//
// Example:
// Input: nums = [3,1,-2,-5,2,-4]
// Output: [3,-2,1,-5,2,-4]
// Explanation:
// The positive integers in nums are [3,1,2]. The negative integers are [-2,-5,-4].
// The only possible way to rearrange them such that they satisfy all conditions is [3,-2,1,-5,2,-4].
// Other ways such as [1,-2,2,-5,3,-4], [3,1,2,-2,-5,-4], [-2,3,-5,1,-4,2] are incorrect because they do not satisfy one or more conditions.
//
// Constraints:
// 2 <= nums.length <= 2 * 105
// 	nums.length is even
// 	1 <= |nums[i]| <= 105
// 	nums consists of equal number of positive and negative integers.
//
//
//  
// It is not required to do the modifications in-place.
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Quicksort (array, two-pointers, randomized)
//   • When to use: Use Quicksort for efficient in-place sorting of arrays, especially when average-case performance and cache efficiency are prioritized. It is suitable for large datasets where memory usage is a concern.
//   • Idea: Quicksort is a divide-and-conquer sorting algorithm that partitions an array around a pivot element, then recursively sorts the two resulting subarrays. Its average time complexity is O(N log N), but can degrade to O(N^2) in the worst case.
//   • Invariants: All elements to the left of the `lt` pointer are less than the pivot value.; All elements to the right of the `gt` pointer are greater than the pivot value.
//   • Tips: Randomly shuffle the input or choose a random pivot to ensure average-case performance.; Employ 3-way partitioning to efficiently handle duplicate keys and avoid quadratic worst-case scenarios.
//   • Pitfalls: Failing to handle duplicate keys can lead to quadratic time complexity.; Incorrect pointer crossing logic can cause infinite loops or array out-of-bounds errors.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] rearrangeArray(int[] nums) {
        int n = nums.length;
        int[] result = new int[n];
        int posIndex = 0;
        int negIndex = 1;

        for (int num : nums) {
            if (num > 0) {
                result[posIndex] = num;
                posIndex += 2;
            } else {
                result[negIndex] = num;
                negIndex += 2;
            }
        }

        return result;          
    }
}
