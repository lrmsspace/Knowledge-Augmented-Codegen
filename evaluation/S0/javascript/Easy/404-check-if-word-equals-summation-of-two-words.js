// Source: https://leetcode.com/problems/check-if-word-equals-summation-of-two-words/   |   Difficulty: Easy
//
// Problem Description:
// The letter value of a letter is its position in the alphabet starting from 0 (i.e. 'a' -> 0, 'b' -> 1, 'c' -> 2, etc.).
//
// The numerical value of some string of lowercase English letters s is the concatenation of the letter values of each letter in s, which is then converted into an integer.
//
//
// 	For example, if s = "acb", we concatenate each letter's letter value, resulting in "021". After converting it, we get 21.
//
//
// You are given three strings firstWord, secondWord, and targetWord, each consisting of lowercase English letters 'a' through 'j' inclusive.
//
// Return true if the summation of the numerical values of firstWord and secondWord equals the numerical value of targetWord, or false otherwise.
//
// Example:
// Input: firstWord = "acb", secondWord = "cba", targetWord = "cdb"
// Output: true
// Explanation:
// The numerical value of firstWord is "acb" -> "021" -> 21.
// The numerical value of secondWord is "cba" -> "210" -> 210.
// The numerical value of targetWord is "cdb" -> "231" -> 231.
// We return true because 21 + 210 == 231.
//
// Constraints:
// 1 <= firstWord.length, secondWord.length, targetWord.length <= 8
// 	firstWord, secondWord, and targetWord consist of lowercase English letters from 'a' to 'j' inclusive.
//

/**
 * @param {string} firstWord
 * @param {string} secondWord
 * @param {string} targetWord
 * @return {boolean}
 */
var isSumEqual = function(firstWord, secondWord, targetWord) {
    const getNumericValue = (word) => {
        let value = 0;
        for (const char of word) {
            value = value * 10 + (char.charCodeAt(0) - 'a'.charCodeAt(0));
        }
        return value;
    };

    return getNumericValue(firstWord) + getNumericValue(secondWord) === getNumericValue(targetWord);
};