// Source: https://leetcode.com/problems/match-substring-after-replacement/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings s and sub. You are also given a 2D character array mappings where mappings[i] = [oldi, newi] indicates that you may perform the following operation any number of times:
//
//
// 	Replace a character oldi of sub with newi.
//
//
// Each character in sub cannot be replaced more than once.
//
// Return true if it is possible to make sub a substring of s by replacing zero or more characters according to mappings. Otherwise, return false.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: s = "fool3e7bar", sub = "leet", mappings = [["e","3"],["t","7"],["t","8"]]
// Output: true
// Explanation: Replace the first 'e' in sub with '3' and 't' in sub with '7'.
// Now sub = "l3e7" is a substring of s, so we return true.
//
// Constraints:
// 1 <= sub.length <= s.length <= 5000
// 	0 <= mappings.length <= 1000
// 	mappings[i].length == 2
// 	oldi != newi
// 	s and sub consist of uppercase and lowercase English letters and digits.
// 	oldi and newi are either uppercase or lowercase English letters or digits.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool matchReplacement(char* s, char* sub, char** mappings, int mappingsSize, int* mappingsColSize) {
    int sLen = strlen(s);
    int subLen = strlen(sub);
    if (subLen > sLen) return false;

    /* Build mapping table */
    bool map[128][128];
    memset(map, 0, sizeof(map));
    for (int i = 0; i < mappingsSize; ++i) {
        char oldc = mappings[i][0];
        char newc = mappings[i][1];
        map[(int)oldc][(int)newc] = true;
    }

    /* Try to match sub at each position in s */
    for (int start = 0; start <= sLen - subLen; ++start) {
        bool matched = true;
        for (int i = 0; i < subLen; ++i) {
            char sc = s[start + i];
            char subc = sub[i];
            if (sc == subc) continue;
            if (!map[(int)subc][(int)sc]) {
                matched = false;
                break;
            }
        }
        if (matched) return true;
    }
    return false;       
}
