// Source: https://leetcode.com/problems/find-the-closest-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.
//
// The closest is defined as the absolute difference minimized between two integers.
//
// Example:
// Input: n = "123"
// Output: "121"
//
// Constraints:
// 1 <= n.length <= 18
// 	n consists of only digits.
// 	n does not have leading zeros.
// 	n is representing an integer in the range [1, 1018 - 1].
//
// Helpful references (internal KB):
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} n
 * @return {string}
 */
var nearestPalindromic = function(n) {
    
    const len = n.length;
    const candidates = new Set();
    // Edge cases: 10...0 and 9...9
    candidates.add((10 ** (len - 1) - 1).toString()); // 999...9
    candidates.add((10 ** len + 1).toString()); // 100...001
    const prefix = parseInt(n.slice(0, Math.ceil(len / 2)));
    for (let i = -1; i <= 1; i++) {
        const newPrefix = (prefix + i).toString();
        let candidate;
        if (len % 2 === 0) {
            candidate = newPrefix + newPrefix.split('').reverse().join('');
        } else {
            candidate = newPrefix + newPrefix.slice(0, -1).split('').reverse().join('');
        }
        candidates.add(candidate);
    }
    candidates.delete(n); // Remove the original number if it's in candidates
    let closest = null;
    for (const candidate of candidates) {
        if (candidate === n) continue;
        if (closest === null ||
            Math.abs(BigInt(candidate) - BigInt(n)) < Math.abs(BigInt(closest) - BigInt(n)) ||
            (Math.abs(BigInt(candidate) - BigInt(n)) === Math.abs(BigInt(closest) - BigInt(n)) && BigInt(candidate) < BigInt(closest)))) {
            closest = candidate;
        }
    }
    return closest;
    
};
