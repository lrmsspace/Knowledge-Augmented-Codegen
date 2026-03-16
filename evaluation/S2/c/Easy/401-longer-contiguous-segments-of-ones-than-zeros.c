// Source: https://leetcode.com/problems/longer-contiguous-segments-of-ones-than-zeros/   |   Difficulty: Easy
//
// Problem Description:
// Given a binary string s, return true if the longest contiguous segment of 1's is strictly longer than the longest contiguous segment of 0's in s, or return false otherwise.
//
//
// 	For example, in s = "110100010" the longest continuous segment of 1s has length 2, and the longest continuous segment of 0s has length 3.
//
//
// Note that if there are no 0's, then the longest continuous segment of 0's is considered to have a length 0. The same applies if there is no 1's.
//
// Example:
// Input: s = "1101"
// Output: true
// Explanation:
// The longest contiguous segment of 1s has length 2: "1101"
// The longest contiguous segment of 0s has length 1: "1101"
// The segment of 1s is longer, so return true.
//
// Constraints:
// 1 <= s.length <= 100
// 	s[i] is either '0' or '1'.
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

bool checkZeroOnes(char* s) {
    int maxOnes = 0, maxZeros = 0;
    int currentOnes = 0, currentZeros = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '1') {
            currentOnes++;
            currentZeros = 0; // reset zeros count
        } else {
            currentZeros++;
            currentOnes = 0; // reset ones count
        }
        if (currentOnes > maxOnes) {
            maxOnes = currentOnes;
        }
        if (currentZeros > maxZeros) {
            maxZeros = currentZeros;
        }
    }

    return maxOnes > maxZeros;      
}
