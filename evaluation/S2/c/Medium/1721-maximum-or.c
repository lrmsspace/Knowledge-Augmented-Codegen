// Source: https://leetcode.com/problems/maximum-or/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n and an integer k. In an operation, you can choose an element and multiply it by 2.
//
// Return the maximum possible value of nums[0] | nums[1] | ... | nums[n - 1] that can be obtained after applying the operation on nums at most k times.
//
// Note that a | b denotes the bitwise or between two integers a and b.
//
// Example:
// Input: nums = [12,9], k = 1
// Output: 30
// Explanation: If we apply the operation to index 1, our new array nums will be equal to [12,18]. Thus, we return the bitwise or of 12 and 18, which is 30.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 15
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

long long maximumOr(int* nums, int numsSize, int k) {
    long long result = 0;
    for (int i = 0; i < numsSize; i++) {
        result |= nums[i];
    }
    
    long long maxOr = result;
    for (int i = 0; i < numsSize; i++) {
        long long currentOr = result - (result & nums[i]) + ((long long)nums[i] << k);
        if (currentOr > maxOr) {
            maxOr = currentOr;
        }
    }
    
    return maxOr;       
}
