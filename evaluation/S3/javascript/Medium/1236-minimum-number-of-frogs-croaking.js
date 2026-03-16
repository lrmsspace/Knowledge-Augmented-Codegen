// Source: https://leetcode.com/problems/minimum-number-of-frogs-croaking/   |   Difficulty: Medium
//
// Problem Description:
// You are given the string croakOfFrogs, which represents a combination of the string "croak" from different frogs, that is, multiple frogs can croak at the same time, so multiple "croak" are mixed.
//
// Return the minimum number of different frogs to finish all the croaks in the given string.
//
// A valid "croak" means a frog is printing five letters 'c', 'r', 'o', 'a', and 'k' sequentially. The frogs have to print all five letters to finish a croak. If the given string is not a combination of a valid "croak" return -1.
//
// Example:
// Input: croakOfFrogs = "croakcroak"
// Output: 1 
// Explanation: One frog yelling "croak" twice.
//
// Constraints:
// 1 <= croakOfFrogs.length <= 105
// 	croakOfFrogs is either 'c', 'r', 'o', 'a', or 'k'.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} croakOfFrogs
 * @return {number}
 */
var minNumberOfFrogs = function(croakOfFrogs) {
    const count = new Array(5).fill(0); // c, r, o, a, k
    const charToIndex = { 'c': 0, 'r': 1, 'o': 2, 'a': 3, 'k': 4 };
    let maxFrogs = 0;
    
    for (const char of croakOfFrogs) {
        const idx = charToIndex[char];
        count[idx]++;
        
        // Ensure the sequence is valid
        if (idx > 0 && count[idx] > count[idx - 1]) {
            return -1; // Invalid sequence
        }
        
        // Update max frogs needed
        maxFrogs = Math.max(maxFrogs, count[0] - count[4]);
    }
    
    // Check if all frogs finished croaking
    if (count[0] !== count[4]) {
        return -1; // Not all frogs finished
    }
    
    return maxFrogs;
};
