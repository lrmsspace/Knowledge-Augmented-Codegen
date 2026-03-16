// Source: https://leetcode.com/problems/string-transformation/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings s and t of equal length n. You can perform the following operation on the string s:
//
//
// 	Remove a suffix of s of length l where 0 < l < n and append it at the start of s.
// 	For example, let s = 'abcd' then in one operation you can remove the suffix 'cd' and append it in front of s making s = 'cdab'.
//
//
// You are also given an integer k. Return the number of ways in which s can be transformed into t in exactly k operations.
//
// Since the answer can be large, return it modulo 109 + 7.
//
// Example:
// Input: s = "abcd", t = "cdab", k = 2
// Output: 2
// Explanation: 
// First way:
// In first operation, choose suffix from index = 3, so resulting s = "dabc".
// In second operation, choose suffix from index = 3, so resulting s = "cdab".
//
// Second way:
// In first operation, choose suffix from index = 1, so resulting s = "bcda".
// In second operation, choose suffix from index = 1, so resulting s = "cdab".
//
// Constraints:
// 2 <= s.length <= 5 * 105
// 	1 <= k <= 1015
// 	s.length == t.length
// 	s and t consist of only lowercase English alphabets.
//
// Helpful references (internal KB):
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
// - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
//   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
//   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
//   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
//   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
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
 * @param {number} k
 * @return {number}
 */
var numberOfWays = function(s, t, k) {
    const MOD = 1e9 + 7;
    const n = s.length;
    // Step 1: Use KMP to find the longest prefix of t that is a suffix of s
    const buildKMPTable = (pattern) => {
        const m = pattern.length;
        const lps = new Array(m).fill(0);
        for (let i = 1; i < m; i++) {
            let j = lps[i - 1];
            while (j > 0 && pattern[i] !== pattern[j]) {
                j = lps[j - 1];
            }
            if (pattern[i] === pattern[j]) {
                j++;
            }
            lps[i] = j;
        }
        return lps;
    }

    const lps = buildKMPTable(t);
    let overlap = 0;
    for (let i = 0; i < n; i++) {
        while (overlap > 0 && s[i] !== t[overlap]) {
            overlap = lps[overlap - 1];
        }
        if (s[i] === t[overlap]) {
            overlap++;
        }
    }

    // Step 2: Calculate the number of ways to achieve the transformation in k steps
    // We can only achieve the transformation if k >= 1 and k <= n (since we can't rotate more than n times)
    if (k < 1 || k > n) {
        return 0;
    }
    // The number of ways to achieve the transformation depends on the overlap and the number of rotations needed
    const rotationsNeeded = (n - overlap) % n;
    if (rotationsNeeded === 0) {
        return 1; // No rotation needed, only one way to achieve the transformation
    }
    // If rotations needed is less than k, we can achieve the transformation in k steps by rotating the suffix of length rotationsNeeded
    if (rotationsNeeded <= k) {
        return 1; // We can achieve the transformation in k steps by rotating the suffix of length rotationsNeeded
    }
    return 0; // We cannot achieve the transformation in k steps
};
