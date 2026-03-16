// Source: https://leetcode.com/problems/find-the-median-of-the-uniqueness-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. The uniqueness array of nums is the sorted array that contains the number of distinct elements of all the subarrays of nums. In other words, it is a sorted array consisting of distinct(nums[i..j]), for all 0 <= i <= j < nums.length.
//
// Here, distinct(nums[i..j]) denotes the number of distinct elements in the subarray that starts at index i and ends at index j.
//
// Return the median of the uniqueness array of nums.
//
// Note that the median of an array is defined as the middle element of the array when it is sorted in non-decreasing order. If there are two choices for a median, the smaller of the two values is taken.
//
// Example:
// Input: nums = [1,2,3]
//
// Output: 1
//
// Explanation:
//
// The uniqueness array of nums is [distinct(nums[0..0]), distinct(nums[1..1]), distinct(nums[2..2]), distinct(nums[0..1]), distinct(nums[1..2]), distinct(nums[0..2])] which is equal to [1, 1, 1, 2, 2, 3]. The uniqueness array has a median of 1. Therefore, the answer is 1.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int medianOfUniquenessArray(int* nums, int numsSize) {
    // Step 1: Calculate the number of distinct elements in all subarrays
    int* distinctCounts = (int*)malloc(numsSize * numsSize * sizeof(int));
    int index = 0;

    for (int i = 0; i < numsSize; i++) {
        int count[100001] = {0}; // To count occurrences of each number
        int distinct = 0;

        for (int j = i; j < numsSize; j++) {
            if (count[nums[j]] == 0) {
                distinct++;
            }
            count[nums[j]]++;
            distinctCounts[index++] = distinct;
        }
    }

    // Step 2: Sort the distinctCounts array
    qsort(distinctCounts, index, sizeof(int), compare);

    // Step 3: Find the median
    int median;
    if (index % 2 == 1) {
        median = distinctCounts[index / 2];
    } else {
        median = distinctCounts[(index / 2) - 1]; // Take the smaller of the two middle values
    }

    free(distinctCounts);
    return median;      
}
