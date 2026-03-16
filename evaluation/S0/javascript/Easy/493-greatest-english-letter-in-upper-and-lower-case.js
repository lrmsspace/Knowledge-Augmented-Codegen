// Source: https://leetcode.com/problems/greatest-english-letter-in-upper-and-lower-case/   |   Difficulty: Easy
//
// Problem Description:
// Given a string of English letters s, return the greatest English letter which occurs as both a lowercase and uppercase letter in s. The returned letter should be in uppercase. If no such letter exists, return an empty string.
//
// An English letter b is greater than another letter a if b appears after a in the English alphabet.
//
// Example:
// Input: s = "lEeTcOdE"
// Output: "E"
// Explanation:
// The letter 'E' is the only letter to appear in both lower and upper case.
//
// Constraints:
// 1 <= s.length <= 1000
// 	s consists of lowercase and uppercase English letters.
//

/**
 * @param {string} s
 * @return {string}
 */
var greatestLetter = function(s) {
    const lowerSet = new Set();
    const upperSet = new Set();
    for (const char of s) {
        if (char >= 'a' && char <= 'z') {
            lowerSet.add(char);
        } else if (char >= 'A' && char <= 'Z') {
            upperSet.add(char);
        }
    }
    for (let i = 25; i >= 0; i--) {
        const upperChar = String.fromCharCode('A'.charCodeAt(0) + i);
        const lowerChar = String.fromCharCode('a'.charCodeAt(0) + i);
        if (upperSet.has(upperChar) && lowerSet.has(lowerChar)) {
            return upperChar;
        }
    }
    return "";
};