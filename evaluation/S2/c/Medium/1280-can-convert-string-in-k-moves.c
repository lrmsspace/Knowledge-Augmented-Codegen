// Source: https://leetcode.com/problems/can-convert-string-in-k-moves/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings s and t, your goal is to convert s into t in k moves or less.
//
// During the ith (1 <= i <= k) move you can:
//
//
// 	Choose any index j (1-indexed) from s, such that 1 <= j <= s.length and j has not been chosen in any previous move, and shift the character at that index i times.
// 	Do nothing.
//
//
// Shifting a character means replacing it by the next letter in the alphabet (wrapping around so that 'z' becomes 'a'). Shifting a character by i means applying the shift operations i times.
//
// Remember that any index j can be picked at most once.
//
// Return true if it's possible to convert s into t in no more than k moves, otherwise return false.
//
// Example:
// Input: s = "input", t = "ouput", k = 9
// Output: true
// Explanation: In the 6th move, we shift 'i' 6 times to get 'o'. And in the 7th move we shift 'n' to get 'u'.
//
// Constraints:
// 1 <= s.length, t.length <= 10^5
// 	0 <= k <= 10^9
// 	s, t contain only lowercase English letters.
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

bool canConvertString(char* s, char* t, int k) {
    int charCount[26] = {0};
    for (int i = 0; s[i] != '\0'; i++) {
        charCount[(s[i] - 'a' + 26) % 26]++;
        charCount[(t[i] - 'a' + 26) % 26]--;
    }

    for (int i = 0; i < 26; i++) {
        if (charCount[i] > 0) {
            int shift = (i - (s[i] - 'a') + 26) % 26;
            if (shift == 0) shift = 26;
            if (shift > k) return false;
            k -= shift;
        }
    }
    return true;        
}
