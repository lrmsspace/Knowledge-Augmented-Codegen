// Source: https://leetcode.com/problems/minimum-window-substring/   |   Difficulty: Hard
//
// Problem Description:
// Given two strings s and t of lengths m and n respectively, return the minimum window substring of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".
//
// The testcases will be generated such that the answer is unique.
//
// Example:
// Input: s = "ADOBECODEBANC", t = "ABC"
// Output: "BANC"
// Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.
//
// Constraints:
// m == s.length
// 	n == t.length
// 	1 <= m, n <= 105
// 	s and t consist of uppercase and lowercase English letters.
//
//
//  
// Follow up: Could you find an algorithm that runs in O(m + n) time?
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
// - Z-function and its calculation (string, array, counting)
//   • When to use: Use when you need to find all occurrences of a pattern within a text, or to identify repeated prefixes within a string efficiently.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the string and its suffix starting at index i. It runs in linear time, O(N), where N is the length of the string.
//   • Invariants: For all j < i, z[j] correctly stores the length of the longest common prefix between S and S[j...].; The segment [l, r-1] represents the rightmost segment that is a prefix of S and has been fully processed.
//   • Tips: Initialize z[0] to 0 (or N, depending on definition) and handle it as a base case.; Utilize previously computed Z-values to avoid redundant comparisons, especially within the 'rightmost matching segment' [l, r].
//   • Pitfalls: Incorrectly updating or using the 'rightmost matching segment' boundaries (l and r).; Off-by-one errors when calculating indices or lengths, especially with 0-based vs. 1-based indexing.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* minWindow(char* s, char* t) {
    // Step 1: Count characters in t
    int tCount[128] = {0}; // Assuming ASCII character set
    for (char* p = t; *p; p++) {
        tCount[(int)(*p)]++;
    }

    // Step 2: Use two pointers to find the minimum window
    int sCount[128] = {0};
    int left = 0, right = 0, minLen = __INT_MAX__, minStart = 0;
    int required = 0; // Number of unique characters in t that need to be present in the window
    for (int i = 0; i < 128; i++) {
        if (tCount[i] > 0) {
            required++;
        }
    }
    int formed = 0; // Number of unique characters in the current window that match the required count

    while (s[right]) {
        char c = s[right];
        sCount[(int)c]++;
        
        // Check if the current character's count matches the required count in t
        if (tCount[(int)c] > 0 && sCount[(int)c] == tCount[(int)c]) {
            formed++;
        }

        // Try to contract the window until it ceases to be 'desirable'
        while (left <= right && formed == required) {
            c = s[left];

            // Update minimum window if a smaller one is found
            if (right - left + 1 < minLen) {
                minLen = right - left + 1;
                minStart = left;
            }

            sCount[(int)c]--;
            if (tCount[(int)c] > 0 && sCount[(int)c] < tCount[(int)c]) {
                formed--;
            }
            left++;
        }
        right++;
    }

    // Step 3: Return the minimum window substring
    if (minLen == __INT_MAX__) {
        return ""; // No valid window found
    } else {
        char* result = (char*)malloc((minLen + 1) * sizeof(char));
        strncpy(result, s + minStart, minLen);
        result[minLen] = '\0'; // Null-terminate the string
        return result;
    }
}
