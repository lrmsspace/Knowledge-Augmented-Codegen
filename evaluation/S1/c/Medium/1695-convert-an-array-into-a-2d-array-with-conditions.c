// Source: https://leetcode.com/problems/convert-an-array-into-a-2d-array-with-conditions/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. You need to create a 2D array from nums satisfying the following conditions:
//
//
// 	The 2D array should contain only the elements of the array nums.
// 	Each row in the 2D array contains distinct integers.
// 	The number of rows in the 2D array should be minimal.
//
//
// Return the resulting array. If there are multiple answers, return any of them.
//
// Note that the 2D array can have a different number of elements on each row.
//
// Example:
// Input: nums = [1,3,4,1,2,3,1]
// Output: [[1,3,4,2],[1,3],[1]]
// Explanation: We can create a 2D array that contains the following rows:
// - 1,3,4,2
// - 1,3
// - 1
// All elements of nums were used, and each row of the 2D array contains distinct integers, so it is a valid answer.
// It can be shown that we cannot have less than 3 rows in a valid array.
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= nums.length
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
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
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findMatrix(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int freq[201] = {0};
    int maxFreq = 0;
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
        if (freq[nums[i]] > maxFreq) {
            maxFreq = freq[nums[i]];
        }
    }

    int** result = (int**)malloc(maxFreq * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxFreq * sizeof(int));
    for (int i = 0; i < maxFreq; i++) {
        result[i] = (int*)malloc(numsSize * sizeof(int));
        (*returnColumnSizes)[i] = 0;
    }

    for (int num = 1; num <= 200; num++) {
        while (freq[num] > 0) {
            result[maxFreq - freq[num]][(*returnColumnSizes)[maxFreq - freq[num]]] = num;
            (*returnColumnSizes)[maxFreq - freq[num]]++;
            freq[num]--;
        }
    }

    *returnSize = maxFreq;
    return result;      
}
