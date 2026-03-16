// Source: https://leetcode.com/problems/form-array-by-concatenating-subarrays-of-another-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array groups of length n. You are also given an integer array nums.
//
// You are asked if you can choose n disjoint subarrays from the array nums such that the ith subarray is equal to groups[i] (0-indexed), and if i > 0, the (i-1)th subarray appears before the ith subarray in nums (i.e. the subarrays must be in the same order as groups).
//
// Return true if you can do this task, and false otherwise.
//
// Note that the subarrays are disjoint if and only if there is no index k such that nums[k] belongs to more than one subarray. A subarray is a contiguous sequence of elements within an array.
//
// Example:
// Input: groups = [[1,-1,-1],[3,-2,0]], nums = [1,-1,0,1,-1,-1,3,-2,0]
// Output: true
// Explanation: You can choose the 0th subarray as [1,-1,0,1,-1,-1,3,-2,0] and the 1st one as [1,-1,0,1,-1,-1,3,-2,0].
// These subarrays are disjoint as they share no common nums[k] element.
//
// Constraints:
// groups.length == n
// 	1 <= n <= 103
// 	1 <= groups[i].length, sum(groups[i].length) <= 103
// 	1 <= nums.length <= 103
// 	-107 <= groups[i][j], nums[k] <= 107
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
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool canChoose(int** groups, int groupsSize, int* groupsColSize, int* nums, int numsSize) {
    int i = 0; // Pointer for nums array
    for (int g = 0; g < groupsSize; g++) {
        int* group = groups[g];
        int groupSize = groupsColSize[g];
        bool found = false;

        while (i <= numsSize - groupSize) {
            bool match = true;
            for (int j = 0; j < groupSize; j++) {
                if (nums[i + j] != group[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                found = true;
                i += groupSize; // Move pointer past the matched subarray
                break;
            }
            i++;
        }

        if (!found) {
            return false; // Current group not found in nums
        }
    }

    return true; // All groups found in order       
}
