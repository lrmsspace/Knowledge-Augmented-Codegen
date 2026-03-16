// Source: https://leetcode.com/problems/hash-divided-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s of length n and an integer k, where n is a multiple of k. Your task is to hash the string s into a new string called result, which has a length of n / k.
//
// First, divide s into n / k substrings, each with a length of k. Then, initialize result as an empty string.
//
// For each substring in order from the beginning:
//
//
// 	The hash value of a character is the index of that character in the English alphabet (e.g., 'a' → 0, 'b' → 1, ..., 'z' → 25).
// 	Calculate the sum of all the hash values of the characters in the substring.
// 	Find the remainder of this sum when divided by 26, which is called hashedChar.
// 	Identify the character in the English lowercase alphabet that corresponds to hashedChar.
// 	Append that character to the end of result.
//
//
// Return result.
//
// Example:
// Input: s = "abcd", k = 2
//
// Output: "bf"
//
// Explanation:
//
// First substring: "ab", 0 + 1 = 1, 1 % 26 = 1, result[0] = 'b'.
//
// Second substring: "cd", 2 + 3 = 5, 5 % 26 = 5, result[1] = 'f'.
//
// Constraints:
// 1 <= k <= 100
// 	k <= s.length <= 1000
// 	s.length is divisible by k.
// 	s consists only of lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, number, hashing)
//   • When to use: Use when needing to compare strings or substrings quickly, reducing comparison time from linear to constant. It is ideal for problems requiring frequent string equality checks or pattern matching across large texts.
//   • Idea: String hashing maps a string to an integer hash value, allowing for O(1) equality checks between strings or substrings. This technique relies on a hash function where equal strings must produce equal hashes, though the reverse is not guaranteed.
//   • Invariants: The hash of any prefix s[0...i] is correctly computed based on s[0...i-1] and s[i].; All characters processed up to the current index i contribute to the current hash value.
//   • Tips: Use a polynomial rolling hash function with a prime base and a large prime modulus.; Employ double hashing (two different bases/moduli) to significantly reduce collision probability.
//   • Pitfalls: Hash collisions: Different strings can produce the same hash, leading to false positives if not handled.; Poor choice of base or modulus can lead to more frequent collisions.
// - Finding repetitions (string, divide-and-conquer, recursion)
//   • When to use: This algorithm is used to find all occurrences of repeating substrings within a given string. It is suitable for problems requiring the identification of periodic patterns or structural redundancies.
//   • Idea: This algorithm, often exemplified by Main-Lorentz, uses a divide-and-conquer strategy with Z-function as a subroutine to efficiently find all repetitions in a string. It typically achieves an O(N log N) time complexity for finding and describing repetitions.
//   • Invariants: All repetitions fully contained within the left or right subproblems are found recursively.; Crossing repetitions are identified by combining information from both subproblems using Z-function.
//   • Tips: Understand the definition of a 'repetition' (e.g., Crochemore triples or (i, p, r) tuples).; Leverage string algorithms like Z-function for efficient substring matching in subproblems.
//   • Pitfalls: Expanding compact repetition tuples to full start/end indices can lead to O(N^2) complexity.; Incorrectly handling string reversal or concatenation for Z-function applications.
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @param {number} k
 * @return {string}
 */
var stringHash = function(s, k) {
    let result = '';
    for (let i = 0; i < s.length; i += k) {
        let sum = 0;
        for (let j = i; j < i + k; j++) {
            sum += s.charCodeAt(j) - 'a'.charCodeAt(0);
        }
        const hashedChar = String.fromCharCode((sum % 26) + 'a'.charCodeAt(0));
        result += hashedChar;
    }
    return result;
};
