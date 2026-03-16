// Source: https://leetcode.com/problems/longest-substring-of-one-repeating-character/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string s. You are also given a 0-indexed string queryCharacters of length k and a 0-indexed array of integer indices queryIndices of length k, both of which are used to describe k queries.
//
// The ith query updates the character in s at index queryIndices[i] to the character queryCharacters[i].
//
// Return an array lengths of length k where lengths[i] is the length of the longest substring of s consisting of only one repeating character after the ith query is performed.
//
// Example:
// Input: s = "babacc", queryCharacters = "bcb", queryIndices = [1,3,3]
// Output: [3,3,4]
// Explanation: 
// - 1st query updates s = "bbbacc". The longest substring consisting of one repeating character is "bbb" with length 3.
// - 2nd query updates s = "bbbccc". 
//   The longest substring consisting of one repeating character can be "bbb" or "ccc" with length 3.
// - 3rd query updates s = "bbbbcc". The longest substring consisting of one repeating character is "bbbb" with length 4.
// Thus, we return [3,3,4].
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	k == queryCharacters.length == queryIndices.length
// 	1 <= k <= 105
// 	queryCharacters consists of lowercase English letters.
// 	0 <= queryIndices[i] < s.length
//
// Helpful references (internal KB):
// - Suffix array (array, tree, string, suffix-array, tree-dp, lca)
//   • When to use: Use when needing to perform fast substring searches, pattern matching, or other string operations on a fixed text, especially when space efficiency is critical compared to suffix trees.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing only their starting indices. It is often paired with an LCP (Longest Common Prefix) array to enable efficient string algorithms, typically achieving O(N log N) or O(N) construction and O(M + log N) or O(M) search complexity.
//   • Invariants: The suffix array `A` stores indices such that `S[A[i]:]` is lexicographically smaller than `S[A[i+1]:]` for all valid `i`.; The `lcp[i]` value represents the length of the longest common prefix between `S[A[i-1]:]` and `S[A[i]:]`.
//   • Tips: Pair with an LCP array to significantly speed up pattern searching and other string queries.; Consider Enhanced Suffix Arrays (ESA) for improved space and time efficiency over suffix trees, especially for large datasets.
//   • Pitfalls: Naive pattern searching without LCP information can be O(M log N), which might be too slow for long patterns.; Construction can be complex to implement efficiently in linear time.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @param {string} queryCharacters
 * @param {number[]} queryIndices
 * @return {number[]}
 */
var longestRepeating = function(s, queryCharacters, queryIndices) {
    const n = s.length, k = queryCharacters.length;
    const arr = s.split('');
    const freq = new Map();
    for (let i = 0, j = 0; j < n; j++) {
        const char = arr[j];
        freq.set(char, (freq.get(char) || 0) + 1);
        while (freq.get(char) > 1) {
            const leftChar = arr[i++];
            freq.set(leftChar, freq.get(leftChar) - 1);
        }
    }
    const result = [];
    for (let i = 0; i < k; i++) {
        const index = queryIndices[i];
        const newChar = queryCharacters[i];
        const oldChar = arr[index];
        arr[index] = newChar;
        freq.set(oldChar, freq.get(oldChar) - 1);
        freq.set(newChar, (freq.get(newChar) || 0) + 1);
        while (freq.get(newChar) > 1) {
            const leftChar = arr[j++];
            freq.set(leftChar, freq.get(leftChar) - 1);
        }
        result.push(j - i);
    }
    return result;
        
};
