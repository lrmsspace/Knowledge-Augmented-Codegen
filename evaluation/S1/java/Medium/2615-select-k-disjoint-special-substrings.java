// Source: https://leetcode.com/problems/select-k-disjoint-special-substrings/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s of length n and an integer k, determine whether it is possible to select k disjoint special substrings.
//
// A special substring is a substring where:
//
//
// 	Any character present inside the substring should not appear outside it in the string.
// 	The substring is not the entire string s.
//
//
// Note that all k substrings must be disjoint, meaning they cannot overlap.
//
// Return true if it is possible to select k such disjoint special substrings; otherwise, return false.
//
// Example:
// Input: s = "abcdbaefab", k = 2
//
// Output: true
//
// Explanation:
//
//
// 	We can select two disjoint special substrings: "cd" and "ef".
// 	"cd" contains the characters 'c' and 'd', which do not appear elsewhere in s.
// 	"ef" contains the characters 'e' and 'f', which do not appear elsewhere in s.
//
// Constraints:
// 2 <= n == s.length <= 5 * 104
// 	0 <= k <= 26
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Substring Search (string, array, kmp)
//   • When to use: Use when needing to find all occurrences or the first occurrence of a pattern string within a larger text string efficiently. It is particularly useful when the pattern might have significant self-overlapping prefixes and suffixes, allowing for linear time complexity.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently searches for occurrences of a pattern within a text by avoiding redundant comparisons. It preprocesses the pattern to build a Deterministic Finite Automaton (DFA) or Longest Proper Prefix Suffix (LPS) array, achieving O(N + M) time complexity.
//   • Invariants: During DFA construction, dfa[c][j] correctly stores the next state if character c is encountered in state j.; During DFA construction, x maintains the length of the longest proper prefix of pattern[0...j-1] that is also a suffix of pattern[0...j-1].
//   • Tips: Precompute the LPS array or DFA for the pattern to guide the search.; The LPS array indicates the longest proper prefix that is also a suffix, enabling efficient shifts.
//   • Pitfalls: Incorrect construction of the LPS array or DFA is a common source of errors.; High constant factors for small alphabets or short patterns might make simpler algorithms faster.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean maxSubstringLength(String s, int k) {
        int[] freq = new int[26];
        for (char c : s.toCharArray()) {
            freq[c - 'a']++;
        }

        int count = 0;
        boolean[] visited = new boolean[26];
        for (char c : s.toCharArray()) {
            if (!visited[c - 'a'] && freq[c - 'a'] == 1) {
                count++;
                visited[c - 'a'] = true;
            }
        }

        return count >= k;          
    }
}
