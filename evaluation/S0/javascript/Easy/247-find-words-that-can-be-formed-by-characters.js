// Source: https://leetcode.com/problems/find-words-that-can-be-formed-by-characters/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of strings words and a string chars.
//
// A string is good if it can be formed by characters from chars (each character can only be used once for each word in words).
//
// Return the sum of lengths of all good strings in words.
//
// Example:
// Input: words = ["cat","bt","hat","tree"], chars = "atach"
// Output: 6
// Explanation: The strings that can be formed are "cat" and "hat" so the answer is 3 + 3 = 6.
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length, chars.length <= 100
// 	words[i] and chars consist of lowercase English letters.
//

/**
 * @param {string[]} words
 * @param {string} chars
 * @return {number}
 */
var countCharacters = function(words, chars) {
    const charCount = {};
    for (const char of chars) {
        charCount[char] = (charCount[char] || 0) + 1;
    }
    let totalLength = 0;
    for (const word of words) {
        const wordCount = {};
        let canForm = true;
        for (const char of word) {
            wordCount[char] = (wordCount[char] || 0) + 1;
            if (wordCount[char] > (charCount[char] || 0)) {
                canForm = false;
                break;
            }
        }
        if (canForm) {
            totalLength += word.length;
        }
    }
    return totalLength;
};