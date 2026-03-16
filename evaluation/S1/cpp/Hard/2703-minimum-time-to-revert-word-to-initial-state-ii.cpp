// Source: https://leetcode.com/problems/minimum-time-to-revert-word-to-initial-state-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string word and an integer k.
//
// At every second, you must perform the following operations:
//
//
// 	Remove the first k characters of word.
// 	Add any k characters to the end of word.
//
//
// Note that you do not necessarily need to add the same characters that you removed. However, you must perform both operations at every second.
//
// Return the minimum time greater than zero required for word to revert to its initial state.
//
// Example:
// Input: word = "abacaba", k = 3
// Output: 2
// Explanation: At the 1st second, we remove characters "aba" from the prefix of word, and add characters "bac" to the end of word. Thus, word becomes equal to "cababac".
// At the 2nd second, we remove characters "cab" from the prefix of word, and add "aba" to the end of word. Thus, word becomes equal to "abacaba" and reverts to its initial state.
// It can be shown that 2 seconds is the minimum time greater than zero required for word to revert to its initial state.
//
// Constraints:
// 1 <= word.length <= 106
// 	1 <= k <= word.length
// 	word consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Z-function and its calculation (string, array, two-pointers)
//   • When to use: Use when you need to find the length of the longest common prefix between a string and all its suffixes efficiently. It is fundamental for various string matching and pattern searching problems.
//   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the original string and its suffix starting at index i. This algorithm calculates the entire Z-array in O(N) time complexity.
//   • Invariants: For all k < i, z[k] has been correctly computed.; The interval [l, r) always represents the rightmost segment match found so far.
//   • Tips: Leverage previously computed Z-values to avoid redundant comparisons.; Maintain a [l, r) window representing the rightmost segment match found so far.
//   • Pitfalls: Incorrectly handling the base case z[0] (usually set to 0).; Off-by-one errors when calculating the length of the prefix or updating the window.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Suffix Automaton (string, enumeration)
//   • When to use: When you need to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings or pattern matching in linear time.
//   • Idea: A Suffix Automaton is a minimal finite automaton that accepts all suffixes of a given string. It implicitly represents all substrings and can be constructed in linear time, O(N) where N is the string length.
//   • Invariants: Every path from the initial state spells a substring of the original string.; Each state represents a set of substrings that share the same end positions in the original string.
//   • Tips: Understand the concept of `endpos` sets and how they define states.; The number of states and transitions in a suffix automaton is linear with respect to string length.
//   • Pitfalls: The construction algorithm can be complex and prone to off-by-one errors or incorrect link updates.; Debugging state transitions and suffix links requires careful attention.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumTimeToInitialState(string word, int k) {
        int n = word.size();
        vector<int> z(n, 0);
        int l = 0, r = 0;
        for (int i = 1; i < n; ++i) {
            if (i < r) {
                z[i] = min(r - i, z[i - l]);
            }
            while (i + z[i] < n && word[z[i]] == word[i + z[i]]) {
                ++z[i];
            }
            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }

        int res = 1;
        for (int t = k; t < n; t += k) {
            if (z[t] < n - t) {
                break;
            }
            ++res;
        }
        return res;         
    }
};
