// Source: https://leetcode.com/problems/increasing-decreasing-string/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s. Reorder the string using the following algorithm:
//
//
// 	Remove the smallest character from s and append it to the result.
// 	Remove the smallest character from s that is greater than the last appended character, and append it to the result.
// 	Repeat step 2 until no more characters can be removed.
// 	Remove the largest character from s and append it to the result.
// 	Remove the largest character from s that is smaller than the last appended character, and append it to the result.
// 	Repeat step 5 until no more characters can be removed.
// 	Repeat steps 1 through 6 until all characters from s have been removed.
//
//
// If the smallest or largest character appears more than once, you may choose any occurrence to append to the result.
//
// Return the resulting string after reordering s using this algorithm.
//
// Example:
// Input: s = "aaaabbbbcccc"
// Output: "abccbaabccba"
// Explanation: After steps 1, 2 and 3 of the first iteration, result = "abc"
// After steps 4, 5 and 6 of the first iteration, result = "abccba"
// First iteration is done. Now s = "aabbcc" and we go back to step 1
// After steps 1, 2 and 3 of the second iteration, result = "abccbaabc"
// After steps 4, 5 and 6 of the second iteration, result = "abccbaabccba"
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of only lowercase English letters.
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
// - Suffix Automaton (graph, string, simulation)
//   • When to use: When needing to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings, finding occurrences, or checking for specific patterns. It provides a compact and powerful data structure for complex string problems.
//   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that recognizes all suffixes of a given string. It compactly represents all substrings of the string, with each state corresponding to an endpos-equivalence class, and can be constructed in linear time O(N).
//   • Invariants: Every state corresponds to a unique endpos-equivalence class of substrings.; For any state, all substrings ending at its endpos set are represented by that state or its ancestors via suffix links.
//   • Tips: Focus on the endpos definition for state equivalence.; Understand the incremental construction process.
//   • Pitfalls: The construction algorithm is non-trivial and prone to off-by-one errors.; Misinterpreting the role of suffix links vs. transition links.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string sortString(string s) {
        int count[26] = {0};
        for (char c : s) {
            count[c - 'a']++;
        }

        string result;
        int n = s.length();
        while (result.length() < n) {
            // Increasing order
            for (int i = 0; i < 26; i++) {
                if (count[i] > 0) {
                    result += (char)(i + 'a');
                    count[i]--;
                }
            }
            // Decreasing order
            for (int i = 25; i >= 0; i--) {
                if (count[i] > 0) {
                    result += (char)(i + 'a');
                    count[i]--;
                }
            }
        }

        return result;          
    }
};
