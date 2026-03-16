// Source: https://leetcode.com/problems/shortest-unsorted-continuous-subarray/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, you need to find one continuous subarray such that if you only sort this subarray in non-decreasing order, then the whole array will be sorted in non-decreasing order.
//
// Return the shortest such subarray and output its length.
//
// Example:
// Input: nums = [2,6,4,8,10,9,15]
// Output: 5
// Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
//
// Constraints:
// 1 <= nums.length <= 104
// 	-105 <= nums[i] <= 105
//
//
//  
// Follow up: Can you solve it in O(n) time complexity?
//
// Helpful references (internal KB):
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Longest increasing subsequence (array, dp-1d, binary-search)
//   • When to use: Use this when you need to find the longest possible subsequence of a given sequence where elements are in strictly increasing order. It is applicable for optimizing problems involving ordered selections from a sequence.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements are sorted in increasing order. It can be solved using dynamic programming in O(N^2) time or with a greedy approach using binary search in O(N log N) time.
//   • Invariants: The 'tails' array (or equivalent) is always sorted in increasing order.; For any index `i`, `tails[i]` stores the smallest ending element of an increasing subsequence of length `i+1` found so far.
//   • Tips: The O(N log N) approach maintains a 'tails' array where tails[i] stores the smallest ending element of an increasing subsequence of length i+1.; Use binary search (specifically `lower_bound` for strictly increasing) to find the correct position to update the 'tails' array.
//   • Pitfalls: Confusing subsequence with subarray; elements do not need to be contiguous.; Incorrectly applying binary search (e.g., using `upper_bound` instead of `lower_bound` for strict increase).
// - Longest increasing subsequence (array, greedy, dp-1d)
//   • When to use: Use when finding the longest sequence of elements in a given array such that each element is greater than the preceding one, without changing their relative order. It's applicable for optimizing problems involving ordered subsets.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of an array where elements are in strictly increasing order. It can be solved in O(N log N) time using a greedy approach with binary search, or O(N^2) using dynamic programming.
//   • Invariants: The 'tails' array elements are always in strictly increasing order.; tails[i] stores the smallest possible ending element of an increasing subsequence of length i+1.
//   • Tips: Prefer the O(N log N) greedy approach with binary search for better performance.; The 'tails' array in the greedy approach stores the smallest tail of all increasing subsequences of a certain length.
//   • Pitfalls: Confusing LIS with Longest Common Subsequence (LCS) or contiguous subarrays.; Incorrectly handling duplicate elements when 'strictly increasing' is required.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int findUnsortedSubarray(int[] nums) {
        int n = nums.length;
        int start = 0, end = n - 1;

        // Find the first element from the left that is out of order
        while (start < n - 1 && nums[start] <= nums[start + 1]) {
            start++;
        }

        // If the array is already sorted
        if (start == n - 1) {
            return 0;
        }

        // Find the first element from the right that is out of order
        while (end > 0 && nums[end] >= nums[end - 1]) {
            end--;
        }

        // Find the minimum and maximum values in the unsorted subarray
        int minVal = Integer.MAX_VALUE, maxVal = Integer.MIN_VALUE;
        for (int i = start; i <= end; i++) {
            minVal = Math.min(minVal, nums[i]);
            maxVal = Math.max(maxVal, nums[i]);
        }

        // Extend the start index to the left if there are elements greater than minVal
        while (start > 0 && nums[start - 1] > minVal) {
            start--;
        }

        // Extend the end index to the right if there are elements less than maxVal
        while (end < n - 1 && nums[end + 1] < maxVal) {
            end++;
        }

        return end - start + 1;         
    }
}
