// Source: https://leetcode.com/problems/number-of-strings-that-appear-as-substrings-in-word/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of strings patterns and a string word, return the number of strings in patterns that exist as a substring in word.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: patterns = ["a","abc","bc","d"], word = "abc"
// Output: 3
// Explanation:
// - "a" appears as a substring in "abc".
// - "abc" appears as a substring in "abc".
// - "bc" appears as a substring in "abc".
// - "d" does not appear as a substring in "abc".
// 3 of the strings in patterns appear as a substring in word.
//
// Constraints:
// 1 <= patterns.length <= 100
// 	1 <= patterns[i].length <= 100
// 	1 <= word.length <= 100
// 	patterns[i] and word consist of lowercase English letters.
//
// Helpful references (internal KB):
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
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
 * @param {string[]} patterns
 * @param {string} word
 * @return {number}
 */
var numOfStrings = function(patterns, word) {
    let count = 0;
    
    for (const pattern of patterns) {
        if (word.includes(pattern)) {
            count++;
        }
    }
    
    return count;
};
