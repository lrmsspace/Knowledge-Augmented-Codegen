// Source: https://leetcode.com/problems/determine-if-two-strings-are-close/   |   Difficulty: Medium
//
// Problem Description:
// Two strings are considered close if you can attain one from the other using the following operations:
//
//
// 	Operation 1: Swap any two existing characters.
//
// 	
// 		For example, abcde -> aecdb
// 	
// 	
// 	Operation 2: Transform every occurrence of one existing character into another existing character, and do the same with the other character.
// 	
// 		For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)
// 	
// 	
//
//
// You can use the operations on either string as many times as necessary.
//
// Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.
//
// Example:
// Input: word1 = "abc", word2 = "bca"
// Output: true
// Explanation: You can attain word2 from word1 in 2 operations.
// Apply Operation 1: "abc" -> "acb"
// Apply Operation 1: "acb" -> "bca"
//
// Constraints:
// 1 <= word1.length, word2.length <= 105
// 	word1 and word2 contain only lowercase English letters.
//

/**
 * @param {string} word1
 * @param {string} word2
 * @return {boolean}
 */
var closeStrings = function(word1, word2) {
    if (word1.length !== word2.length) return false;

    const freq1 = Array(26).fill(0);
    const freq2 = Array(26).fill(0);
    const charSet1 = new Set();
    const charSet2 = new Set();
    for (const char of word1) {
        freq1[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
        charSet1.add(char);
    }
    for (const char of word2) {
        freq2[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
        charSet2.add(char);
    }
    if (charSet1.size !== charSet2.size) return false;
    for (const char of charSet1) {
        if (!charSet2.has(char)) return false;
    }
    freq1.sort((a, b) => a - b);
    freq2.sort((a, b) => a - b);
    for (let i = 0; i < 26; i++) {
        if (freq1[i] !== freq2[i]) return false;
    }
    return true;
};