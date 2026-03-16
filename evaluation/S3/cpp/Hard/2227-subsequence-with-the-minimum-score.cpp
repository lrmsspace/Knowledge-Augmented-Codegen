// Source: https://leetcode.com/problems/subsequence-with-the-minimum-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings s and t.
//
// You are allowed to remove any number of characters from the string t.
//
// The score of the string is 0 if no characters are removed from the string t, otherwise:
//
//
// 	Let left be the minimum index among all removed characters.
// 	Let right be the maximum index among all removed characters.
//
//
// Then the score of the string is right - left + 1.
//
// Return the minimum possible score to make t a subsequence of s.
//
// A subsequence of a string is a new string that is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ace" is a subsequence of "abcde" while "aec" is not).
//
// Example:
// Input: s = "abacaba", t = "bzaa"
// Output: 1
// Explanation: In this example, we remove the character "z" at index 1 (0-indexed).
// The string t becomes "baa" which is a subsequence of the string "abacaba" and the score is 1 - 1 + 1 = 1.
// It can be proven that 1 is the minimum score that we can achieve.
//
// Constraints:
// 1 <= s.length, t.length <= 105
// 	s and t consist of only lowercase English letters.
//
// Helpful references (internal KB):
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, two-pointers)
//   • When to use: When efficiently searching for all occurrences of a pattern string within a larger text string, or when computing the longest proper prefix of a string that is also a suffix for all its prefixes.
//   • Idea: The KMP algorithm efficiently finds all occurrences of a pattern within a text by pre-processing the pattern to build a prefix function (LPS array), which avoids redundant character comparisons. It achieves a time complexity of O(N + M) for text length N and pattern length M.
//   • Invariants: The prefix function array `pi` stores for each `i` the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation for `pi[i]`, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix of `s[0...i-1]`.
//   • Tips: Precompute the prefix function (LPS array) for the pattern to guide shifts.; Use two pointers: one for the text (or current character in pattern for prefix function), one for the pattern (or length of matched prefix).
//   • Pitfalls: Incorrectly calculating or using the prefix function values, leading to wrong shifts.; Off-by-one errors when indexing or shifting pointers, especially at boundaries.
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumScore(string s, string t) {
        int n = s.length(), m = t.length();
        vector<int> left(m, -1), right(m, -1);
        for (int i = 0, j = 0; i < n && j < m; ++i) {
            if (s[i] == t[j]) {
                left[j] = i;
                ++j;
            }
        }
        for (int i = n - 1, j = m - 1; i >= 0 && j >= 0; --i) {
            if (s[i] == t[j]) {
                right[j] = i;
                --j;
            }
        }
        int minScore = m; 
        for (int i = 0; i < m; ++i) {
            if (left[i] == -1) { 
                minScore = min(minScore, m - i); 
            } else if (right[i] == -1) { 
                minScore = min(minScore, i + 1); 
            } else { 
                minScore = min(minScore, right[i] - left[i] + 1); 
            }
        }
        return minScore;
    }
};
