// Source: https://leetcode.com/problems/binary-number-with-alternating-bits/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer, check whether it has alternating bits: namely, if two adjacent bits will always have different values.
//
// Example:
// Input: n = 5
// Output: true
// Explanation: The binary representation of 5 is: 101
//
// Constraints:
// 1 <= n <= 231 - 1
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

bool hasAlternatingBits(int n) {
    // Get the last bit of n
    int last_bit = n & 1;
    // Right shift n to process the next bit
    n >>= 1;

    while (n > 0) {
        // Get the current last bit of n
        int current_bit = n & 1;
        // Check if the current bit is the same as the last bit
        if (current_bit == last_bit) {
            return false; // Found two adjacent bits that are the same
        }
        // Update last_bit and right shift n for the next iteration
        last_bit = current_bit;
        n >>= 1;
    }

    return true; // All adjacent bits are different     
}
