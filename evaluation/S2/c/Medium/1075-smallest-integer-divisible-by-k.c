// Source: https://leetcode.com/problems/smallest-integer-divisible-by-k/   |   Difficulty: Medium
//
// Problem Description:
// Given a positive integer k, you need to find the length of the smallest positive integer n such that n is divisible by k, and n only contains the digit 1.
//
// Return the length of n. If there is no such n, return -1.
//
// Note: n may not fit in a 64-bit signed integer.
//
// Example:
// Input: k = 1
// Output: 1
// Explanation: The smallest answer is n = 1, which has length 1.
//
// Constraints:
// 1 <= k <= 105
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

int smallestRepunitDivByK(int k) {
    if (k % 2 == 0 || k % 5 == 0) {
        return -1; // If k is divisible by 2 or 5, there is no such n
    }
    
    int remainder = 0;
    for (int length = 1; length <= k; length++) {
        remainder = (remainder * 10 + 1) % k; // Generate the next number consisting of '1's
        if (remainder == 0) {
            return length; // Found the smallest n that is divisible by k
        }
    }
    
    return -1; // If we exhaust all possibilities up to length k, return -1     
}
