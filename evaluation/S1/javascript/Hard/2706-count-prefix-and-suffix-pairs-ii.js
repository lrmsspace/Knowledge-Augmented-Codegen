// Source: https://leetcode.com/problems/count-prefix-and-suffix-pairs-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string array words.
//
// Let's define a boolean function isPrefixAndSuffix that takes two strings, str1 and str2:
//
//
// 	isPrefixAndSuffix(str1, str2) returns true if str1 is both a prefix and a suffix of str2, and false otherwise.
//
//
// For example, isPrefixAndSuffix("aba", "ababa") is true because "aba" is a prefix of "ababa" and also a suffix, but isPrefixAndSuffix("abc", "abcd") is false.
//
// Return an integer denoting the number of index pairs (i, j) such that i < j, and isPrefixAndSuffix(words[i], words[j]) is true.
//
// Example:
// Input: words = ["a","aba","ababa","aa"]
// Output: 4
// Explanation: In this example, the counted index pairs are:
// i = 0 and j = 1 because isPrefixAndSuffix("a", "aba") is true.
// i = 0 and j = 2 because isPrefixAndSuffix("a", "ababa") is true.
// i = 0 and j = 3 because isPrefixAndSuffix("a", "aa") is true.
// i = 1 and j = 2 because isPrefixAndSuffix("aba", "ababa") is true.
// Therefore, the answer is 4.
//
// Constraints:
// 1 <= words.length <= 105
// 	1 <= words[i].length <= 105
// 	words[i] consists only of lowercase English letters.
// 	The sum of the lengths of all words[i] does not exceed 5 * 105.
//
// Helpful references (internal KB):
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, two-pointers)
//   • When to use: When efficiently searching for all occurrences of a pattern string within a larger text string, or when computing the longest proper prefix of a string that is also a suffix for all its prefixes.
//   • Idea: The KMP algorithm efficiently finds all occurrences of a pattern within a text by pre-processing the pattern to build a prefix function (LPS array), which avoids redundant character comparisons. It achieves a time complexity of O(N + M) for text length N and pattern length M.
//   • Invariants: The prefix function array `pi` stores for each `i` the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation for `pi[i]`, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix of `s[0...i-1]`.
//   • Tips: Precompute the prefix function (LPS array) for the pattern to guide shifts.; Use two pointers: one for the text (or current character in pattern for prefix function), one for the pattern (or length of matched prefix).
//   • Pitfalls: Incorrectly calculating or using the prefix function values, leading to wrong shifts.; Off-by-one errors when indexing or shifting pointers, especially at boundaries.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Suffix Array (string, array, merge-sort)
//   • When to use: Use when needing to efficiently query properties of all suffixes or substrings of a given text, especially for pattern matching or finding repeated structures. It is particularly useful for problems requiring lexicographical ordering of all suffixes.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices. It enables efficient string operations like pattern searching and finding longest common prefixes, typically constructed in O(N log N) time.
//   • Invariants: After k iterations, suffixes are sorted correctly up to a certain length (e.g., 2^k).; All suffixes of the original string are represented by their starting indices in the array.
//   • Tips: Append a unique sentinel character (e.g., '$') smaller than any other character to the string.; Utilize the LCP array, often built alongside, for advanced string queries and optimizations.
//   • Pitfalls: Naive sorting of suffixes by string comparison leads to an inefficient O(N^2 log N) complexity.; High memory usage for very long strings due to storing all suffixes implicitly or explicitly.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[]} words
 * @return {number}
 */
var countPrefixSuffixPairs = function(words) {
    let count = 0;
    for (let i = 0; i < words.length; i++) {
        for (let j = i + 1; j < words.length; j++) {
            if (isPrefixAndSuffix(words[i], words[j])) {
                count++;
            }
        }
    }
    return count;
};
