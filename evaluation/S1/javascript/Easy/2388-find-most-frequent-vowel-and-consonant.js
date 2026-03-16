// Source: https://leetcode.com/problems/find-most-frequent-vowel-and-consonant/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s consisting of lowercase English letters ('a' to 'z'). 
//
// Your task is to:
//
//
// 	Find the vowel (one of 'a', 'e', 'i', 'o', or 'u') with the maximum frequency.
// 	Find the consonant (all other letters excluding vowels) with the maximum frequency.
//
//
// Return the sum of the two frequencies.
//
// Note: If multiple vowels or consonants have the same maximum frequency, you may choose any one of them. If there are no vowels or no consonants in the string, consider their frequency as 0.
// The frequency of a letter x is the number of times it occurs in the string.
//
// Example:
// Input: s = "successes"
//
// Output: 6
//
// Explanation:
//
//
// 	The vowels are: 'u' (frequency 1), 'e' (frequency 2). The maximum frequency is 2.
// 	The consonants are: 's' (frequency 4), 'c' (frequency 2). The maximum frequency is 4.
// 	The output is 2 + 4 = 6.
//
// Constraints:
// 1 <= s.length <= 100
// 	s consists of lowercase English letters only.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Fibonacci Numbers (number, greedy, enumeration)
//   • When to use: When you need a unique, non-ambiguous binary representation of positive integers based on Fibonacci numbers, ensuring no two consecutive Fibonacci numbers are used in the sum.
//   • Idea: This algorithm encodes a positive integer into a unique binary string by greedily finding its Zeckendorf representation (sum of non-consecutive Fibonacci numbers). The encoding process typically involves iterating through Fibonacci numbers, resulting in a logarithmic time complexity relative to the input number's magnitude.
//   • Invariants: The remaining value 'n' to be encoded is always non-negative.; The partial binary code constructed so far represents a valid Zeckendorf sum of non-consecutive Fibonacci numbers.
//   • Tips: Precompute Fibonacci numbers up to a certain limit to optimize lookups.; Always start with the largest Fibonacci number less than or equal to the target value.
//   • Pitfalls: Incorrectly handling the base cases for small numbers like 1 or 2.; Forgetting to append the mandatory final '1' bit to the codeword.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {number}
 */
var maxFreqSum = function(s) {
    const vowelSet = new Set(['a', 'e', 'i', 'o', 'u']);
    const freqMap = new Map();
    for (const char of s) {
        freqMap.set(char, (freqMap.get(char) || 0) + 1);
    }
    let maxVowelFreq = 0;
    let maxConsonantFreq = 0;
    for (const [char, freq] of freqMap.entries()) {
        if (vowelSet.has(char)) {
            maxVowelFreq = Math.max(maxVowelFreq, freq);
        } else {
            maxConsonantFreq = Math.max(maxConsonantFreq, freq);
        }
    }
    return maxVowelFreq + maxConsonantFreq;
};
