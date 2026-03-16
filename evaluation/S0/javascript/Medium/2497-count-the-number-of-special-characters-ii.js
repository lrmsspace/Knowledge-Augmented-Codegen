// Source: https://leetcode.com/problems/count-the-number-of-special-characters-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word. A letter c is called special if it appears both in lowercase and uppercase in word, and every lowercase occurrence of c appears before the first uppercase occurrence of c.
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
// The special characters are 'a', 'b', and 'c'.
//
// Constraints:
// 1 <= word.length <= 2 * 105
// 	word consists of only lowercase and uppercase English letters.
//

/**
 * @param {string} word
 * @return {number}
 */
var numberOfSpecialChars = function(word) {
    const seenLower = new Set();
    const seenUpper = new Set();
    let specialCount = 0;

    for (const char of word) {
        if (char === char.toLowerCase()) {
            seenLower.add(char);
        } else {
            seenUpper.add(char.toLowerCase());
        }
    }

    for (const char of seenLower) {
        if (seenUpper.has(char)) {
            specialCount++;
        }
    }

    return specialCount;
};