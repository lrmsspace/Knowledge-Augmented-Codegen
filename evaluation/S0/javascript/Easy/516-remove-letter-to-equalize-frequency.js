// Source: https://leetcode.com/problems/remove-letter-to-equalize-frequency/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed string word, consisting of lowercase English letters. You need to select one index and remove the letter at that index from word so that the frequency of every letter present in word is equal.
//
// Return true if it is possible to remove one letter so that the frequency of all letters in word are equal, and false otherwise.
//
// Note:
//
//
// 	The frequency of a letter x is the number of times it occurs in the string.
// 	You must remove exactly one letter and cannot choose to do nothing.
//
// Example:
// Input: word = "abcc"
// Output: true
// Explanation: Select index 3 and delete it: word becomes "abc" and each character has a frequency of 1.
//
// Constraints:
// 2 <= word.length <= 100
// 	word consists of lowercase English letters only.
//

/**
 * @param {string} word
 * @return {boolean}
 */
var equalFrequency = function(word) {
    const freqMap = new Map();
    for (const char of word) {
        freqMap.set(char, (freqMap.get(char) || 0) + 1);
    }

    for (const [char, freq] of freqMap.entries()) {
        freqMap.set(char, freq - 1);
        const values = Array.from(freqMap.values());
        const uniqueValues = new Set(values);
        if (uniqueValues.size === 1) {
            return true;
        }
        freqMap.set(char, freq);
    }

    return false;
};