// Source: https://leetcode.com/problems/count-the-number-of-special-characters-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string word. A letter is called special if it appears both in lowercase and uppercase in word.
//
// Return the number of special letters in word.
//
// Example:
// Input: word = "aaAbcBC"
//
// Output: 3
//
// Explanation:
//
// The special characters in word are 'a', 'b', and 'c'.
//
// Constraints:
// 1 <= word.length <= 50
// 	word consists of only lowercase and uppercase English letters.
//

/**
 * @param {string} word
 * @return {number}
 */
var numberOfSpecialChars = function(word) {
    const lowerSet = new Set();
    const upperSet = new Set();
    for (const char of word) {
        if (char >= 'a' && char <= 'z') {
            lowerSet.add(char);
        } else if (char >= 'A' && char <= 'Z') {
            upperSet.add(char);
        }
    }
    let count = 0;
    for (const char of lowerSet) {
        if (upperSet.has(char.toUpperCase())) {
            count++;
        }
    }
    return count;
};