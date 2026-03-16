// Source: https://leetcode.com/problems/check-if-all-1s-are-at-least-length-k-places-away/   |   Difficulty: Easy
//
// Problem Description:
// Given an binary array nums and an integer k, return true if all 1's are at least k places away from each other, otherwise return false.
//
// Example:
// Input: nums = [1,0,0,0,1,0,0,1], k = 2
// Output: true
// Explanation: Each of the 1s are at least 2 places away from each other.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= k <= nums.length
// 	nums[i] is 0 or 1
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

bool kLengthApart(int* nums, int numsSize, int k) {
    int lastOneIndex = -1; // Initialize to -1 to indicate no 1 has been found yet

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 1) {
            if (lastOneIndex != -1 && (i - lastOneIndex) <= k) {
                return false; // Found two 1's that are too close
            }
            lastOneIndex = i; // Update the index of the last found 1
        }
    }

    return true; // All 1's are at least k places away      
}
