// Source: https://leetcode.com/problems/buddy-strings/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and goal, return true if you can swap two letters in s so the result is equal to goal, otherwise, return false.
//
// Swapping letters is defined as taking two indices i and j (0-indexed) such that i != j and swapping the characters at s[i] and s[j].
//
//
// 	For example, swapping at indices 0 and 2 in "abcd" results in "cbad".
//
// Example:
// Input: s = "ab", goal = "ba"
// Output: true
// Explanation: You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is equal to goal.
//
// Constraints:
// 1 <= s.length, goal.length <= 2 * 104
// 	s and goal consist of lowercase letters.
//
// Helpful references (internal KB):
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Elementary Sorts (array, enumeration)
//   • When to use: Selection sort is simple but inefficient. It's suitable for very small datasets or educational purposes where simplicity of implementation is prioritized over performance.
//   • Idea: Selection sort repeatedly finds the minimum element from the unsorted portion of the array and places it at the beginning of the sorted portion. It has a time complexity of O(N^2) and a space complexity of O(1).
//   • Invariants: The elements in the prefix of the array are sorted.; All elements in the sorted prefix are less than or equal to all elements in the unsorted suffix.
//   • Tips: Easy to understand and implement.; Performs a minimal number of swaps (exactly N-1 swaps).
//   • Pitfalls: Inefficient for large datasets due to O(N^2) time complexity.; Performance is not affected by the initial order of elements.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool buddyStrings(char* s, char* goal) {
    int len_s = 0, len_goal = 0;
    while (s[len_s] != '\0') len_s++;
    while (goal[len_goal] != '\0') len_goal++;
    if (len_s != len_goal) return false;

    if (len_s == 1) return false;

    int diff_indices[2];
    int diff_count = 0;
    int char_count[26] = {0};
    bool has_duplicate = false;

    for (int i = 0; i < len_s; i++) {
        if (s[i] != goal[i]) {
            if (diff_count >= 2) return false;
            diff_indices[diff_count++] = i;
        }
        char_count[s[i] - 'a']++;
        if (char_count[s[i] - 'a'] > 1) {
            has_duplicate = true;
        }
    }

    if (diff_count == 2) {
        return s[diff_indices[0]] == goal[diff_indices[1]] &&
               s[diff_indices[1]] == goal[diff_indices[0]];
    } else if (diff_count == 0) {
        return has_duplicate;
    } else {
        return false;
    }       
}
