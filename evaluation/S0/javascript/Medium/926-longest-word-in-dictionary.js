// Source: https://leetcode.com/problems/longest-word-in-dictionary/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings words representing an English Dictionary, return the longest word in words that can be built one character at a time by other words in words.
//
// If there is more than one possible answer, return the longest word with the smallest lexicographical order. If there is no answer, return the empty string.
//
// Note that the word should be built from left to right with each additional character being added to the end of a previous word.
//
// Example:
// Input: words = ["w","wo","wor","worl","world"]
// Output: "world"
// Explanation: The word "world" can be built one character at a time by "w", "wo", "wor", and "worl".
//
// Constraints:
// 1 <= words.length <= 1000
// 	1 <= words[i].length <= 30
// 	words[i] consists of lowercase English letters.
//

/**
 * @param {string[]} words
 * @return {string}
 */
var longestWord = function(words) {
    const wordSet = new Set(words);
    let longest = '';
    for (const word of words) {
        if (word.length > longest.length || (word.length === longest.length && word < longest)) {
            let canBuild = true;
            for (let i = 1; i < word.length; i++) {
                if (!wordSet.has(word.substring(0, i))) {
                    canBuild = false;
                    break;
                }
            }
            if (canBuild) {
                longest = word;
            }
        }
    }
    return longest;
};