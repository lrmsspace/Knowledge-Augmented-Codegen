// Source: https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the decimal value of the binary string formed by concatenating the binary representations of 1 to n in order, modulo 109 + 7.
//
// Example:
// Input: n = 1
// Output: 1
// Explanation: "1" in binary corresponds to the decimal value 1.
//
// Constraints:
// 1 <= n <= 105
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



int concatenatedBinary(int n){
    long long result = 0;
    int mod = 1000000007;
    
    for (int i = 1; i <= n; i++) {
        // Calculate the number of bits in the current number
        int bits = 0;
        int temp = i;
        while (temp > 0) {
            bits++;
            temp >>= 1;
        }
        
        // Shift the result to the left by the number of bits and add the current number
        result = ((result << bits) | i) % mod;
    }
    
    return (int)result;
}
