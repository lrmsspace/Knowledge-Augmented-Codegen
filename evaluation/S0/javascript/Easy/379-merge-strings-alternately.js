// Source: https://leetcode.com/problems/merge-strings-alternately/   |   Difficulty: Easy
//
// Problem Description:
// You are given two strings word1 and word2. Merge the strings by adding letters in alternating order, starting with word1. If a string is longer than the other, append the additional letters onto the end of the merged string.
//
// Return the merged string.
//
// Example:
// Input: word1 = "abc", word2 = "pqr"
// Output: "apbqcr"
// Explanation: The merged string will be merged as so:
// word1:  a   b   c
// word2:    p   q   r
// merged: a p b q c r
//
// Constraints:
// 1 <= word1.length, word2.length <= 100
// 	word1 and word2 consist of lowercase English letters.
//

/**
 * @param {string} word1
 * @param {string} word2
 * @return {string}
 */
var mergeAlternately = function(word1, word2) {
    let merged = '';
    const maxLength = Math.max(word1.length, word2.length);
    for (let i = 0; i < maxLength; i++) {
        if (i < word1.length) {
            merged += word1[i];
        }
        if (i < word2.length) {
            merged += word2[i];
        }
    }
    return merged;
};