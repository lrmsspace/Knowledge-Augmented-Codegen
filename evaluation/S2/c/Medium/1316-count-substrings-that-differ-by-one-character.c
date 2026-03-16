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
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countSubstrings(char* s, char* t) {
    int count = 0;
    for (int i = 0; s[i]; i++) {
        for (int j = 0; t[j]; j++) {
            int diff = 0;
            for (int k = 0; s[i + k] && t[j + k]; k++) {
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
