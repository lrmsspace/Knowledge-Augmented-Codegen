// Source: https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays with positive integers arr1 and arr2.
//
// A prefix of a positive integer is an integer formed by one or more of its digits, starting from its leftmost digit. For example, 123 is a prefix of the integer 12345, while 234 is not.
//
// A common prefix of two integers a and b is an integer c, such that c is a prefix of both a and b. For example, 5655359 and 56554 have common prefixes 565 and 5655 while 1223 and 43456 do not have a common prefix.
//
// You need to find the length of the longest common prefix between all pairs of integers (x, y) such that x belongs to arr1 and y belongs to arr2.
//
// Return the length of the longest common prefix among all pairs. If no common prefix exists among them, return 0.
//
// Example:
// Input: arr1 = [1,10,100], arr2 = [1000]
// Output: 3
// Explanation: There are 3 pairs (arr1[i], arr2[j]):
// - The longest common prefix of (1, 1000) is 1.
// - The longest common prefix of (10, 1000) is 10.
// - The longest common prefix of (100, 1000) is 100.
// The longest common prefix is 100 with a length of 3.
//
// Constraints:
// 1 <= arr1.length, arr2.length <= 5 * 104
// 	1 <= arr1[i], arr2[i] <= 108
//
// Helpful references (internal KB):
// - Aho-Corasick Algorithm for Pattern Searching (string, array, aho-corasick, enumeration)
//   • When to use: Use when you need to find all occurrences of a fixed set of patterns (a dictionary) within a larger text efficiently. It is particularly effective for scenarios with many patterns or long texts where patterns might overlap.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses this automaton to search for all pattern occurrences in a text in a single pass. It achieves a time complexity of O(N + M + K) where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: The trie structure correctly represents all prefixes of all patterns in the dictionary.; Each node's failure link points to the longest proper suffix of the string ending at that node which is also a prefix in the trie.
//   • Tips: Build the trie first from all patterns, marking terminal nodes.; Compute failure links using a BFS-like approach, similar to KMP's LPS array.
//   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to handle output links (dictionary links) will miss patterns found via failure transitions.
// - Tries (trie, array, trie-match)
//   • When to use: Use when managing string keys in a symbol table and needing efficient prefix, wildcard, or longest prefix matching operations, offering flexibility beyond binary search trees and speed comparable to hashing.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set or associative array where keys are typically strings. It allows for efficient retrieval of keys based on their prefixes, achieving O(L) time complexity for operations, where L is the key length.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node exists only if it is part of at least one stored key.
//   • Tips: Choose an appropriate branching factor (R) based on the alphabet size.; Represent children using arrays for fixed alphabets or hash maps for sparse ones.
//   • Pitfalls: High memory consumption for large alphabets or sparse data.; Deletion of keys can be complex, requiring careful handling of empty branches.
// - Tries (trie, tree, trie-match)
//   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
//   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
//   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        int longest = 0;
        for (int x : arr1) {
            for (int y : arr2) {
                int prefixLength = 0;
                while (x > 0 && y > 0 && x % 10 == y % 10) {
                    prefixLength++;
                    x /= 10;
                    y /= 10;
                }
                longest = max(longest, prefixLength);
            }
        }
        return longest;         
    }
};
