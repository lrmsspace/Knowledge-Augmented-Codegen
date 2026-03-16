// Source: https://leetcode.com/problems/detect-capital/   |   Difficulty: Easy
//
// Problem Description:
// We define the usage of capitals in a word to be right when one of the following cases holds:
//
//
// 	All letters in this word are capitals, like "USA".
// 	All letters in this word are not capitals, like "leetcode".
// 	Only the first letter in this word is capital, like "Google".
//
//
// Given a string word, return true if the usage of capitals in it is right.
//
// Example:
// Input: word = "USA"
// Output: true
//
// Constraints:
// 1 <= word.length <= 100
// 	word consists of lowercase and uppercase English letters.
//

/**
 * @param {string} word
 * @return {boolean}
 */
var detectCapitalUse = function(word) {
    const isUpperCase = (char) => char >= 'A' && char <= 'Z';

    const allUpperCase = word.split('').every(char => isUpperCase(char));
    const allLowerCase = word.split('').every(char => !isUpperCase(char));
    const firstUpperRestLower = isUpperCase(word[0]) && word.slice(1).split('').every(char => !isUpperCase(char));
    
    return allUpperCase || allLowerCase || firstUpperRestLower;     
};
