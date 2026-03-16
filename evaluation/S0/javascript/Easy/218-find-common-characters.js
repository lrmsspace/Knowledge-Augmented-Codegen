// Source: https://leetcode.com/problems/find-common-characters/   |   Difficulty: Easy
//
// Problem Description:
// Given a string array words, return an array of all characters that show up in all strings within the words (including duplicates). You may return the answer in any order.
//
// Example:
// Input: words = ["bella","label","roller"]
// Output: ["e","l","l"]
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 100
// 	words[i] consists of lowercase English letters.
//

/**
 * @param {string[]} words
 * @return {string[]}
 */
var commonChars = function(words) {
    const minFreq = new Array(26).fill(Infinity);
    for (const word of words) {
        const freq = new Array(26).fill(0);
        for (const char of word) {
            freq[char.charCodeAt(0) - 97]++;
        }
        for (let i = 0; i < 26; i++) {
            minFreq[i] = Math.min(minFreq[i], freq[i]);
        }
    }
    const result = [];
    for (let i = 0; i < 26; i++) {
        for (let j = 0; j < minFreq[i]; j++) {
            result.push(String.fromCharCode(i + 97));
        }
    }
    return result;
};