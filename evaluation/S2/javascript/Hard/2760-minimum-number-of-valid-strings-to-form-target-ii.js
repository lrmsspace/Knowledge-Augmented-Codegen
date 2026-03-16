// Source: https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of strings words and a string target.
//
// A string x is called valid if x is a prefix of any string in words.
//
// Return the minimum number of valid strings that can be concatenated to form target. If it is not possible to form target, return -1.
//
// Example:
// Input: words = ["abc","aaaaa","bcdef"], target = "aabcdabc"
//
// Output: 3
//
// Explanation:
//
// The target string can be formed by concatenating:
//
//
// 	Prefix of length 2 of words[1], i.e. "aa".
// 	Prefix of length 3 of words[2], i.e. "bcd".
// 	Prefix of length 3 of words[0], i.e. "abc".
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 5 * 104
// 	The input is generated such that sum(words[i].length) <= 105.
// 	words[i] consists only of lowercase English letters.
// 	1 <= target.length <= 5 * 104
// 	target consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-1d)
//   • When to use: Used for efficient string searching and pattern matching in linear time. It's also fundamental for various string algorithms that leverage self-matching properties.
//   • Idea: The prefix function computes for each position in a string the length of the longest proper prefix of its substring that is also a suffix of that substring. This forms the core of the Knuth-Morris-Pratt (KMP) algorithm, enabling linear time O(N) string matching.
//   • Invariants: For each i, pi[i] is the length of the longest proper prefix of s[0...i] that is also a suffix of s[0...i].; The current j (length of the matched prefix) always represents pi[i-1] or a shorter valid prefix length.
//   • Tips: The prefix function array (pi array) stores lengths, not indices.; It can be used to build the KMP automaton for pattern matching.
//   • Pitfalls: Confusing proper prefix/suffix with non-proper ones.; Incorrectly handling the base case pi[0] = 0.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
// - Aho-Corasick Algorithm for Pattern Searching (trie, queue, bitset, aho-corasick, bfs)
//   • When to use: Use when searching for multiple patterns simultaneously within a larger text. It is highly efficient for finding all occurrences of a dictionary of keywords.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a set of patterns, allowing efficient simultaneous searching for all patterns in a text. It typically achieves O(N + M + K) time complexity, where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: All patterns in the dictionary are correctly represented as paths in the trie structure.; For any state `s`, its failure link `fail[s]` points to the longest proper prefix of the string represented by `s` that is also a suffix of `s` and exists in the trie.
//   • Tips: Build the trie first from all patterns, representing each pattern as a path.; Use BFS to construct failure links, pointing to the longest proper prefix of the current state's string that is also a suffix.
//   • Pitfalls: Incorrectly building failure links can lead to wrong matches or infinite loops.; High memory usage if the pattern set is very large or patterns are excessively long.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[]} words
 * @param {string} target
 * @return {number}
 */
var minValidStrings = function(words, target) {
    const n = words.length;
    const m = target.length;
    const dp = new Array(m + 1).fill(Infinity);
    dp[0] = 0;
    for (let i = 0; i < n; i++) {
        const word = words[i];
        let j = 0;
        for (let k = 0; k < word.length && j < m; k++) {
            if (word[k] === target[j]) {
                j++;
            }
        }
        if (j > 0) {
            for (let k = m - j; k >= 0; k--) {
                dp[k + j] = Math.min(dp[k + j], dp[k] + 1);
            }
        }
    }
    return dp[m] === Infinity ? -1 : dp[m];
};