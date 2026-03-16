// Source: https://leetcode.com/problems/count-vowels-permutation/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, your task is to count how many strings of length n can be formed under the following rules:
//
//
// 	Each character is a lower case vowel ('a', 'e', 'i', 'o', 'u')
// 	Each vowel 'a' may only be followed by an 'e'.
// 	Each vowel 'e' may only be followed by an 'a' or an 'i'.
// 	Each vowel 'i' may not be followed by another 'i'.
// 	Each vowel 'o' may only be followed by an 'i' or a 'u'.
// 	Each vowel 'u' may only be followed by an 'a'.
//
//
// Since the answer may be too large, return it modulo 10^9 + 7.
//
// Example:
// Input: n = 1
// Output: 5
// Explanation: All possible strings are: "a", "e", "i" , "o" and "u".
//
// Constraints:
// 1 <= n <= 2 * 10^4
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

int countVowelPermutation(int n) {
    int mod = 1000000007;
    long a = 1, e = 1, i = 1, o = 1, u = 1;
    for (int j = 2; j <= n; j++) {
        long a_new = (e + i + u) % mod;
        long e_new = (a + i) % mod;
        long i_new = (e + o) % mod;
        long o_new = i % mod;
        long u_new = (i + o) % mod;
        a = a_new;
        e = e_new;
        i = i_new;
        o = o_new;
        u = u_new;
    }
    return (a + e + i + o + u) % mod;       
}
