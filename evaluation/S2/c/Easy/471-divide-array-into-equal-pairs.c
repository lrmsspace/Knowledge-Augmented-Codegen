// Source: https://leetcode.com/problems/divide-array-into-equal-pairs/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums consisting of 2 * n integers.
//
// You need to divide nums into n pairs such that:
//
//
// 	Each element belongs to exactly one pair.
// 	The elements present in a pair are equal.
//
//
// Return true if nums can be divided into n pairs, otherwise return false.
//
// Example:
// Input: nums = [3,2,3,2,2,2]
// Output: true
// Explanation: 
// There are 6 elements in nums, so they should be divided into 6 / 2 = 3 pairs.
// If nums is divided into the pairs (2, 2), (3, 3), and (2, 2), it will satisfy all the conditions.
//
// Constraints:
// nums.length == 2 * n
// 	1 <= n <= 500
// 	1 <= nums[i] <= 500
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

bool divideArray(int* nums, int numsSize) {
    int count[501] = {0}; // Since nums[i] is between 1 and 500

    // Count the occurrences of each number
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }

    // Check if each number occurs an even number of times
    for (int i = 1; i <= 500; i++) {
        if (count[i] % 2 != 0) {
            return false; // If any number occurs an odd number of times, return false
        }
    }

    return true; // All numbers occur an even number of times, return true      
}
