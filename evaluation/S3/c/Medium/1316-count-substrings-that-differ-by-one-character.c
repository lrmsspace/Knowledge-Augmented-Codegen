// Source: https://leetcode.com/problems/count-substrings-that-differ-by-one-character/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings s and t, find the number of ways you can choose a non-empty substring of s and replace a single character by a different character such that the resulting substring is a substring of t. In other words, find the number of substrings in s that differ from some substring in t by exactly one character.
//
// For example, the underlined substrings in "computer" and "computation" only differ by the 'e'/'a', so this is a valid way.
//
// Return the number of substrings that satisfy the condition above.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "aba", t = "baba"
// Output: 6
// Explanation: The following are the pairs of substrings from s and t that differ by exactly 1 character:
// ("aba", "baba")
// ("aba", "baba")
// ("aba", "baba")
// ("aba", "baba")
// ("aba", "baba")
// ("aba", "baba")
// The underlined portions are the substrings that are chosen from s and t.
//
// ​​Example 2:
//
//
// Input: s = "ab", t = "bb"
// Output: 3
// Explanation: The following are the pairs of substrings from s and t that differ by 1 character:
// ("ab", "bb")
// ("ab", "bb")
// ("ab", "bb")
// ​​​​The underlined portions are the substrings that are chosen from s and t.
//
// Constraints:
// 1 <= s.length, t.length <= 100
// 	s and t consist of lowercase English letters only.
//
// Helpful references (internal KB):
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
//   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
//   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
//   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
//   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
// - Suffix array (array, tree, string, suffix-array, tree-dp, lca)
//   • When to use: Use when needing to perform fast substring searches, pattern matching, or other string operations on a fixed text, especially when space efficiency is critical compared to suffix trees.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing only their starting indices. It is often paired with an LCP (Longest Common Prefix) array to enable efficient string algorithms, typically achieving O(N log N) or O(N) construction and O(M + log N) or O(M) search complexity.
//   • Invariants: The suffix array `A` stores indices such that `S[A[i]:]` is lexicographically smaller than `S[A[i+1]:]` for all valid `i`.; The `lcp[i]` value represents the length of the longest common prefix between `S[A[i-1]:]` and `S[A[i]:]`.
//   • Tips: Pair with an LCP array to significantly speed up pattern searching and other string queries.; Consider Enhanced Suffix Arrays (ESA) for improved space and time efficiency over suffix trees, especially for large datasets.
//   • Pitfalls: Naive pattern searching without LCP information can be O(M log N), which might be too slow for long patterns.; Construction can be complex to implement efficiently in linear time.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countSubstrings(char* s, char* t) {
    int count = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        for (int j = 0; t[j] != '\0'; j++) {
            int diff = 0;
            for (int k = 0; s[i + k] != '\0' && t[j + k] != '\0'; k++) {
                if (s[i + k] != t[j + k]) {
                    diff++;
                }
                if (diff > 1) {
                    break;
                }
                if (diff == 1) {
                    count++;
                }
            }
        }
    }
    return count;       
}
