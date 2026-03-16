// Source: https://leetcode.com/problems/check-if-it-is-a-good-array/   |   Difficulty: Hard
//
// Problem Description:
// Given an array nums of positive integers. Your task is to select some subset of nums, multiply each element by an integer and add all these numbers. The array is said to be good if you can obtain a sum of 1 from the array by any possible subset and multiplicand.
//
// Return True if the array is good otherwise return False.
//
// Example:
// Input: nums = [12,5,7,23]
// Output: true
// Explanation: Pick numbers 5 and 7.
// 5*3 + 7*(-2) = 1
//
// Constraints:
// 1 <= nums.length <= 10^5
// 	1 <= nums[i] <= 10^9
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

bool isGoodArray(int* nums, int numsSize) {
    int gcd = nums[0];
    for (int i = 1; i < numsSize; i++) {
        int a = gcd, b = nums[i];
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        gcd = a;
        if (gcd == 1) {
            return true;
        }
    }
    return gcd == 1;        
}
