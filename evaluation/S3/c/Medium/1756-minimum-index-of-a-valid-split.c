// Source: https://leetcode.com/problems/minimum-index-of-a-valid-split/   |   Difficulty: Medium
//
// Problem Description:
// An element x of an integer array arr of length m is dominant if more than half the elements of arr have a value of x.
//
// You are given a 0-indexed integer array nums of length n with one dominant element.
//
// You can split nums at an index i into two arrays nums[0, ..., i] and nums[i + 1, ..., n - 1], but the split is only valid if:
//
//
// 	0 <= i < n - 1
// 	nums[0, ..., i], and nums[i + 1, ..., n - 1] have the same dominant element.
//
//
// Here, nums[i, ..., j] denotes the subarray of nums starting at index i and ending at index j, both ends being inclusive. Particularly, if j < i then nums[i, ..., j] denotes an empty subarray.
//
// Return the minimum index of a valid split. If no valid split exists, return -1.
//
// Example:
// Input: nums = [1,2,2,2]
// Output: 2
// Explanation: We can split the array at index 2 to obtain arrays [1,2,2] and [2]. 
// In array [1,2,2], element 2 is dominant since it occurs twice in the array and 2 * 2 > 3. 
// In array [2], element 2 is dominant since it occurs once in the array and 1 * 2 > 1.
// Both [1,2,2] and [2] have the same dominant element as nums, so this is a valid split. 
// It can be shown that index 2 is the minimum index of a valid split.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	nums has exactly one dominant element.
//
// Helpful references (internal KB):
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumIndex(int* nums, int numsSize) {
    int count = 0, candidate = -1;
    for (int i = 0; i < numsSize; ++i) {
        if (count == 0) {
            candidate = nums[i];
            count = 1;
        } else if (nums[i] == candidate) {
            ++count;
        } else {
            --count;
        }
    }

    int leftCount = 0, rightCount = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == candidate) {
            ++rightCount;
        }
    }

    for (int i = 0; i < numsSize - 1; ++i) {
        if (nums[i] == candidate) {
            ++leftCount;
            --rightCount;
        }

        if (leftCount * 2 > i + 1 && rightCount * 2 > numsSize - i - 1) {
            return i;
        }
    }

    return -1;      
}
