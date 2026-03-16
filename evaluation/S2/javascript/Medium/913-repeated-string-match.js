// Source: https://leetcode.com/problems/repeated-string-match/   |   Difficulty: Medium
//
// Problem Description:
// Given two strings a and b, return the minimum number of times you should repeat string a so that string b is a substring of it. If it is impossible for b​​​​​​ to be a substring of a after repeating it, return -1.
//
// Notice: string "abc" repeated 0 times is "", repeated 1 time is "abc" and repeated 2 times is "abcabc".
//
// Example:
// Input: a = "abcd", b = "cdabcdab"
// Output: 3
// Explanation: We return 3 because by repeating a three times "abcdabcdabcd", b is a substring of it.
//
// Constraints:
// 1 <= a.length, b.length <= 104
// 	a and b consist of lowercase English letters.
//
// Helpful references (internal KB):
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
// - String Hashing (string, number, hashing)
//   • When to use: When comparing strings or substrings efficiently, especially for equality checks or finding duplicates, to reduce comparison time from O(m) to O(1) on average.
//   • Idea: String hashing converts a string into a numerical value (hash) using a polynomial rolling hash function, allowing for O(1) average-case comparison of strings or substrings. This technique typically involves modular arithmetic to keep hash values within a manageable range.
//   • Invariants: The hash of any prefix s[0...i] is correctly calculated based on the chosen base and modulus.; Precomputed powers of the base 'p' are available and correct for all required string lengths.
//   • Tips: Convert characters to integers starting from 1 (e.g., 'a' -> 1) to avoid zero hashes for strings like 'a', 'aa'.; Precompute powers of the base 'p' and their modular inverses for efficient rolling hash calculations.
//   • Pitfalls: Choosing 'a' -> 0 can lead to identical hashes for strings like 'a', 'aa', 'aaa', causing false positives.; Using a single hash function can lead to collisions, where different strings produce the same hash, requiring careful handling.
// - Finding repetitions (string, divide-and-conquer, recursion)
//   • When to use: This algorithm is used to find all occurrences of repeating substrings within a given string. It is suitable for problems requiring the identification of periodic patterns or structural redundancies.
//   • Idea: This algorithm, often exemplified by Main-Lorentz, uses a divide-and-conquer strategy with Z-function as a subroutine to efficiently find all repetitions in a string. It typically achieves an O(N log N) time complexity for finding and describing repetitions.
//   • Invariants: All repetitions fully contained within the left or right subproblems are found recursively.; Crossing repetitions are identified by combining information from both subproblems using Z-function.
//   • Tips: Understand the definition of a 'repetition' (e.g., Crochemore triples or (i, p, r) tuples).; Leverage string algorithms like Z-function for efficient substring matching in subproblems.
//   • Pitfalls: Expanding compact repetition tuples to full start/end indices can lead to O(N^2) complexity.; Incorrectly handling string reversal or concatenation for Z-function applications.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} a
 * @param {string} b
 * @return {number}
 */
var repeatedStringMatch = function(a, b) {
    let repeated = a, count = 1;
    while (repeated.length < b.length) {
        repeated += a;
        count++;
    }
    if (repeated.includes(b)) return count;
    if ((repeated + a).includes(b)) return count + 1;
    return -1;
};
