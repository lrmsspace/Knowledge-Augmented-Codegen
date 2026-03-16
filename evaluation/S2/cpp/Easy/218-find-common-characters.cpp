// Source: https://leetcode.com/problems/find-common-characters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string array words, return an array of all characters that show up in all strings within the words (including duplicates). You may return the answer in any order.
//
// Example:
// Input: words = ["bella","label","roller"]
// Output: ["e","l","l"]
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 100
// 	words[i] consists of lowercase English letters.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Aho-Corasick algorithm (trie, array, trie-match)
//   • When to use: Use when you need to find all occurrences of a fixed set of multiple patterns within a larger text efficiently. It's particularly effective when patterns can overlap or share prefixes.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a set of patterns using a trie and failure links, enabling efficient simultaneous search for all patterns in a text. It achieves a time complexity of O(N + M + K).
//   • Invariants: Every path from the root to a node in the trie represents a unique prefix of at least one pattern.; After processing a character, the current automaton state corresponds to the longest suffix of the processed text that is also a prefix of some pattern.
//   • Tips: Construct the trie from all patterns first, then compute failure links.; Compute failure links using a BFS-like traversal from the root.
//   • Pitfalls: Incorrectly computing failure links, especially for nodes at depth 1 or for non-existent transitions.; Failing to implement output links, leading to missed matches for patterns that are suffixes of others.
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<string> commonChars(vector<string>& words) {
        vector<int> common(26, INT_MAX);
        for (const string& word : words) {
            vector<int> count(26, 0);
            for (char c : word) {
                count[c - 'a']++;
            }
            for (int i = 0; i < 26; ++i) {
                common[i] = min(common[i], count[i]);
            }
        }

        vector<string> result;
        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < common[i]; ++j) {
                result.push_back(string(1, 'a' + i));
            }
        }
        return result;          
    }
};
