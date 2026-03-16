// Source: https://leetcode.com/problems/minimum-substring-partition-of-equal-character-frequency/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s, you need to partition it into one or more balanced substrings. For example, if s == "ababcc" then ("abab", "c", "c"), ("ab", "abc", "c"), and ("ababcc") are all valid partitions, but ("a", "bab", "cc"), ("aba", "bc", "c"), and ("ab", "abcc") are not. The unbalanced substrings are bolded.
//
// Return the minimum number of substrings that you can partition s into.
//
// Note: A balanced string is a string where each character in the string occurs the same number of times.
//
// Example:
// Input: s = "fabccddg"
//
// Output: 3
//
// Explanation:
//
// We can partition the string s into 3 substrings in one of the following ways: ("fab, "ccdd", "g"), or ("fabc", "cd", "dg").
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists only of English lowercase letters.
//
// Helpful references (internal KB):
// - Suffix Automaton (string, simulation)
//   • When to use: Use when needing to efficiently process all substrings or suffixes of a given string, especially for counting distinct substrings, finding occurrences, or other complex string pattern problems. It provides linear time solutions for many tasks.
//   • Idea: A suffix automaton is a directed acyclic graph that compactly represents all distinct substrings of a given string. It enables solving a wide range of string-related problems in linear time, typically O(N) or O(N log A) where N is string length and A is alphabet size.
//   • Invariants: Every path from the initial state corresponds to a distinct substring of the original string.; Each state in the automaton represents a set of substrings that share the same end positions.
//   • Tips: Understand the two types of links: suffix links (parent) and transition links (children).; Construction is typically incremental, adding characters one by one.
//   • Pitfalls: Implementation complexity is high; careful handling of state creation and link updates is crucial.; Off-by-one errors in length calculations or suffix link assignments are common.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Balanced bracket sequences (number, counting)
//   • When to use: When asked to count the total number of valid or well-formed bracket sequences of a certain length or with a specific number of pairs. This often involves combinatorial reasoning or dynamic programming.
//   • Idea: Counts the total number of valid bracket sequences of a given length or with a specific number of pairs, where each opening bracket has a corresponding closing bracket. This problem often has a combinatorial solution, typically involving Catalan numbers, with a time complexity of O(N) or O(N^2) for DP.
//   • Invariants: At any prefix of the sequence, the number of open brackets is greater than or equal to the number of closing brackets.; The total number of open brackets in the sequence equals the total number of closing brackets.
//   • Tips: Recognize the pattern for Catalan numbers if applicable.; Dynamic programming can be used for more complex variations.
//   • Pitfalls: Incorrectly handling the balance constraint (open count >= close count).; Overcounting or undercounting sequences.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumSubstringsInPartition(char* s) {
    int count[26] = {0};
    int i, substrings = 0, unique_chars = 0;

    for (i = 0; s[i] != '\0'; i++) {
        int index = s[i] - 'a';
        count[index]++;

        if (count[index] == 1) {
            unique_chars++;
        }

        int balanced = 1;
        for (int j = 0; j < 26; j++) {
            if (count[j] != 0 && count[j] != count[index]) {
                balanced = 0;
                break;
            }
        }

        if (balanced && unique_chars > 0) {
            substrings++;
            for (int j = 0; j < 26; j++) {
                count[j] = 0;
            }
            unique_chars = 0;
        }
    }

    return substrings;      
}
