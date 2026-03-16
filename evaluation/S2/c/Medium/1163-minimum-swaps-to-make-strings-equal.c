// Source: https://leetcode.com/problems/minimum-swaps-to-make-strings-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s1 and s2 of equal length consisting of letters "x" and "y" only. Your task is to make these two strings equal to each other. You can swap any two characters that belong to different strings, which means: swap s1[i] and s2[j].
//
// Return the minimum number of swaps required to make s1 and s2 equal, or return -1 if it is impossible to do so.
//
// Example:
// Input: s1 = "xx", s2 = "yy"
// Output: 1
// Explanation: Swap s1[0] and s2[1], s1 = "yx", s2 = "yx".
//
// Constraints:
// 1 <= s1.length, s2.length <= 1000
// 	s1.length == s2.length
// 	s1, s2 only contain 'x' or 'y'.
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

int minimumSwap(char* s1, char* s2) {
    int count_x = 0, count_y = 0;
    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] != s2[i]) {
            if (s1[i] == 'x') {
                count_x++;
            } else {
                count_y++;
            }
        }
    }

    // If the total number of mismatches is odd, it's impossible to make the strings equal
    if ((count_x + count_y) % 2 != 0) {
        return -1;
    }

    // Calculate the number of swaps needed
    int swaps = count_x / 2 + count_y / 2; // Pairs of mismatches can be resolved with one swap
    if (count_x % 2 != 0) { // If there's an odd mismatch left, it will require one more swap
        swaps += 2; // One swap to resolve the odd mismatch and another to fix the remaining mismatch
    }

    return swaps;       
}
