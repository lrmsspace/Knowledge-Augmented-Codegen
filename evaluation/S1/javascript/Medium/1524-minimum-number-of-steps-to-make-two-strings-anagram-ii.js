// Source: https://leetcode.com/problems/minimum-number-of-steps-to-make-two-strings-anagram-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given two strings s and t. In one step, you can append any character to either s or t.
//
// Return the minimum number of steps to make s and t anagrams of each other.
//
// An anagram of a string is a string that contains the same characters with a different (or the same) ordering.
//
// Example:
// Input: s = "leetcode", t = "coats"
// Output: 7
// Explanation: 
// - In 2 steps, we can append the letters in "as" onto s = "leetcode", forming s = "leetcodeas".
// - In 5 steps, we can append the letters in "leede" onto t = "coats", forming t = "coatsleede".
// "leetcodeas" and "coatsleede" are now anagrams of each other.
// We used a total of 2 + 5 = 7 steps.
// It can be shown that there is no way to make them anagrams of each other with less than 7 steps.
//
// Constraints:
// 1 <= s.length, t.length <= 2 * 105
// 	s and t consist of lowercase English letters.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
// - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
//   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
//   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
//   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
//   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
//   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @param {string} t
 * @return {number}
 */
var minSteps = function(s, t) {
    const charCount = new Array(26).fill(0);
    const aCharCode = 'a'.charCodeAt(0);

    for (const char of s) {
        charCount[char.charCodeAt(0) - aCharCode]++;
    }

    for (const char of t) {
        charCount[char.charCodeAt(0) - aCharCode]--;
    }

    let steps = 0;
    for (const count of charCount) {
        steps += Math.abs(count);
    }

    return steps;
};
