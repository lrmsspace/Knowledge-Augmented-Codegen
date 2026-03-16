// Source: https://leetcode.com/problems/minimum-additions-to-make-valid-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a string word to which you can insert letters "a", "b" or "c" anywhere and any number of times, return the minimum number of letters that must be inserted so that word becomes valid.
//
// A string is called valid if it can be formed by concatenating the string "abc" several times.
//
// Example:
// Input: word = "b"
// Output: 2
// Explanation: Insert the letter "a" right before "b", and the letter "c" right next to "b" to obtain the valid string "abc".
//
// Constraints:
// 1 <= word.length <= 50
// 	word consists of letters "a", "b" and "c" only.
//

/**
 * @param {string} word
 * @return {number}
 */
var addMinimum = function(word) {
    let additions = 0;
    let expectedChar = 'a';
    for (const char of word) {
        while (char !== expectedChar) {
            additions++;
            expectedChar = expectedChar === 'a' ? 'b' : expectedChar === 'b' ? 'c' : 'a';
        }
        expectedChar = expectedChar === 'a' ? 'b' : expectedChar === 'b' ? 'c' : 'a';
    }
    if (expectedChar !== 'a') {
        additions += (3 - (expectedChar.charCodeAt(0) - 'a'.charCodeAt(0)));
    }
    return additions;
        
};
