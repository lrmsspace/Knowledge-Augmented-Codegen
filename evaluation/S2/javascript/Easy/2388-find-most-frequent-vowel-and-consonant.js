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
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
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
    const freqMap = {};
    
    for (const char of s) {
        freqMap[char] = (freqMap[char] || 0) + 1;
    }
    
    let maxVowelFreq = 0;
    let maxConsonantFreq = 0;
    
    for (const [char, freq] of Object.entries(freqMap)) {
        if (vowelSet.has(char)) {
            maxVowelFreq = Math.max(maxVowelFreq, freq);
        } else {
            maxConsonantFreq = Math.max(maxConsonantFreq, freq);
        }
    }
    
    return maxVowelFreq + maxConsonantFreq;
};
