// Source: https://leetcode.com/problems/maximum-repeating-substring/   |   Difficulty: Easy
//
// Problem Description:
// For a string sequence, a string word is k-repeating if word concatenated k times is a substring of sequence. The word's maximum k-repeating value is the highest value k where word is k-repeating in sequence. If word is not a substring of sequence, word's maximum k-repeating value is 0.
//
// Given strings sequence and word, return the maximum k-repeating value of word in sequence.
//
// Example:
// Input: sequence = "ababc", word = "ab"
// Output: 2
// Explanation: "abab" is a substring in "ababc".
//
// Constraints:
// 1 <= sequence.length <= 100
// 	1 <= word.length <= 100
// 	sequence and word contains only lowercase English letters.
//

/**
 * @param {string} sequence
 * @param {string} word
 * @return {number}
 */
var maxRepeating = function(sequence, word) {
    let maxCount = 0;
    let currentCount = 0;
    let repeatedWord = word;
    while (sequence.includes(repeatedWord)) {
        currentCount++;
        if (currentCount > maxCount) {
            maxCount = currentCount;
        }
        repeatedWord += word;
    }
    return maxCount;
};