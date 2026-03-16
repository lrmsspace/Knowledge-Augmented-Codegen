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
// - Finding repetitions (string, array, z-function, enumeration)
//   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
//   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
//   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
//   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
//   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
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
    const vowels = new Set(['a', 'e', 'i', 'o', 'u']); // Define a set of vowels for quick lookup
    const freq = new Array(26).fill(0); // Initialize an array to count the frequency of each letter (26 lowercase English letters)
    for (const char of s) { // Iterate through each character in the input string
        freq[char.charCodeAt(0) - 'a'.charCodeAt(0)]++; // Increment the frequency count for the current character
    }
    let maxVowelFreq = 0; // Initialize a variable to keep track of the maximum vowel frequency
    let maxConsonantFreq = 0;                                               
    for (let i = 0; i < 26; i++) { // Iterate through the frequency array to find the maximum frequencies for vowels and consonants
        const char = String.fromCharCode(i + 'a'.charCodeAt(0));
        if (vowels.has(char)) { // Check if the current character is a vowel
            maxVowelFreq = Math.max(maxVowelFreq, freq[i]); // Update the maximum vowel frequency if the current frequency is higher
        }
        else { // If it's not a vowel, it must be a consonant
            maxConsonantFreq = Math.max(maxConsonantFreq, freq[i]); // Update the maximum consonant frequency if the current frequency is higher
        }
    }
    return maxVowelFreq + maxConsonantFreq; // Return the sum of the maximum vowel and consonant frequencies
};
