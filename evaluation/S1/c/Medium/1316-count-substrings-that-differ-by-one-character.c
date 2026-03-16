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
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countSubstrings(char* s, char* t) {
    int count = 0;
    int len_s = 0, len_t = 0;

    // Calculate lengths of s and t
    while (s[len_s] != '\0') len_s++;
    while (t[len_t] != '\0') len_t++;

    // Iterate through all possible starting points in s
    for (int i = 0; i < len_s; i++) {
        // Iterate through all possible starting points in t
        for (int j = 0; j < len_t; j++) {
            int diff = 0;
            // Compare substrings starting at s[i] and t[j]
            for (int k = 0; (i + k < len_s) && (j + k < len_t); k++) {
                if (s[i + k] != t[j + k]) {
                    diff++;
                }
                // If exactly one character differs, increment count
                if (diff == 1) {
                    count++;
                }
                // If more than one character differs, break
                if (diff > 1) {
                    break;
                }
            }
        }
    }

    return count;       
}
