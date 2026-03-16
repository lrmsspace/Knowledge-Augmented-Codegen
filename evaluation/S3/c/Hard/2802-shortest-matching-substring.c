// Source: https://leetcode.com/problems/shortest-matching-substring/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s and a pattern string p, where p contains exactly two '*' characters.
//
// The '*' in p matches any sequence of zero or more characters.
//
// Return the length of the shortest substring in s that matches p. If there is no such substring, return -1.
// Note: The empty substring is considered valid.
//
// Example:
// Input: s = "abaacbaecebce", p = "ba*c*ce"
//
// Output: 8
//
// Explanation:
//
// The shortest matching substring of p in s is "baecebce".
//
// Constraints:
// 1 <= s.length <= 105
// 	2 <= p.length <= 105
// 	s contains only lowercase English letters.
// 	p contains only lowercase English letters and exactly two '*'.
//
// Helpful references (internal KB):
// - Z-function and its calculation (string, array, counting)
//   • When to use: Use when you need to find all occurrences of a pattern within a text, or to identify repeated prefixes within a string efficiently.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the string and its suffix starting at index i. It runs in linear time, O(N), where N is the length of the string.
//   • Invariants: For all j < i, z[j] correctly stores the length of the longest common prefix between S and S[j...].; The segment [l, r-1] represents the rightmost segment that is a prefix of S and has been fully processed.
//   • Tips: Initialize z[0] to 0 (or N, depending on definition) and handle it as a base case.; Utilize previously computed Z-values to avoid redundant comparisons, especially within the 'rightmost matching segment' [l, r].
//   • Pitfalls: Incorrectly updating or using the 'rightmost matching segment' boundaries (l and r).; Off-by-one errors when calculating indices or lengths, especially with 0-based vs. 1-based indexing.
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int shortestMatchingSubstring(char* s, char* p) {
    int n = strlen(s), m = strlen(p);
    int star1 = -1, star2 = -1;
    for (int i = 0; i < m; ++i) {
        if (p[i] == '*') {
            if (star1 == -1) star1 = i;
            else star2 = i;
        }
    }
    if (star1 == -1 || star2 == -1) return -1;

    int leftLen = star1, midLen = star2 - star1 - 1, rightLen = m - star2 - 1;
    int minLen = INT_MAX;

    for (int i = 0; i <= n - leftLen; ++i) {
        if (strncmp(s + i, p, leftLen) == 0) {
            for (int j = n; j >= rightLen; --j) {
                if (strncmp(s + j - rightLen, p + star2 + 1, rightLen) == 0) {
                    int midStart = i + leftLen;
                    int midEnd = j - rightLen;
                    if (midStart <= midEnd && strncmp(s + midStart, p + star1 + 1, midLen) == 0) {
                        minLen = fmin(minLen, j - i);
                    }
                }
            }
        }
    }

    return minLen == INT_MAX ? -1 : minLen;     
}
