// Source: https://leetcode.com/problems/minimum-number-of-swaps-to-make-the-binary-string-alternating/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s, return the minimum number of character swaps to make it alternating, or -1 if it is impossible.
//
// The string is called alternating if no two adjacent characters are equal. For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
//
// Any two characters may be swapped, even if they are not adjacent.
//
// Example:
// Input: s = "111000"
// Output: 1
// Explanation: Swap positions 1 and 4: "111000" -> "101010"
// The string is now alternating.
//
// Constraints:
// 1 <= s.length <= 1000
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

int minSwaps(char* s) {
    int count0 = 0, count1 = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '0') {
            count0++;
        } else {
            count1++;
        }
    }

    int n = count0 + count1;
    if (abs(count0 - count1) > 1) {
        return -1; // Impossible to make alternating
    }

    int swaps = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        if ((i % 2 == 0 && s[i] != '0') || (i % 2 == 1 && s[i] != '1')) {
            swaps++;
        }
    }

    // If there are more '1's, we need to swap the odd positions, otherwise the even positions
    if (count1 > count0) {
        return swaps / 2;
    } else {
        return (n - swaps) / 2;
    }       
}
