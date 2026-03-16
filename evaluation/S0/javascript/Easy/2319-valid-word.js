// Source: https://leetcode.com/problems/valid-word/   |   Difficulty: Easy
//
// Problem Description:
// A word is considered valid if:
//
//
// 	It contains a minimum of 3 characters.
// 	It contains only digits (0-9), and English letters (uppercase and lowercase).
// 	It includes at least one vowel.
// 	It includes at least one consonant.
//
//
// You are given a string word.
//
// Return true if word is valid, otherwise, return false.
//
// Example:
// Input: word = "234Adas"
//
// Output: true
//
// Explanation:
//
// This word satisfies the conditions.
//
// Constraints:
// 1 <= word.length <= 20
// 	word consists of English uppercase and lowercase letters, digits, '@', '#', and '$'.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} word
 * @return {boolean}
 */
var isValid = function(word) {
    if (word.length < 3) return false;
    const vowels = new Set(['a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U']);
    let hasVowel = false;
    let hasConsonant = false;
    for (const char of word) {
        if (!(/[a-zA-Z0-9]/).test(char)) {
            return false;
        }
        if (vowels.has(char)) {
            hasVowel = true;
        } else if ((/[a-zA-Z]/).test(char)) {
            hasConsonant = true;
        }
    }
    return hasVowel && hasConsonant;
};