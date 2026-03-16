// Source: https://leetcode.com/problems/keyboard-row/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of strings words, return the words that can be typed using letters of the alphabet on only one row of American keyboard like the image below.
//
// Note that the strings are case-insensitive, both lowercased and uppercased of the same letter are treated as if they are at the same row.
//
// In the American keyboard:
//
//
// 	the first row consists of the characters "qwertyuiop",
// 	the second row consists of the characters "asdfghjkl", and
// 	the third row consists of the characters "zxcvbnm".
//
// Example:
// Input: words = ["Hello","Alaska","Dad","Peace"]
//
// Output: ["Alaska","Dad"]
//
// Explanation:
//
// Both "a" and "A" are in the 2nd row of the American keyboard due to case insensitivity.
//
// Constraints:
// 1 <= words.length <= 20
// 	1 <= words[i].length <= 100
// 	words[i] consists of English letters (both lowercase and uppercase).
//

/**
 * @param {string[]} words
 * @return {string[]}
 */
var findWords = function(words) {
    const row1 = new Set(['q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p']);
    const row2 = new Set(['a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l']);
    const row3 = new Set(['z', 'x', 'c', 'v', 'b', 'n', 'm']);
    const result = [];

    for (const word of words) {
        const lowerWord = word.toLowerCase();
        let targetRow;
        if (row1.has(lowerWord[0])) {
            targetRow = row1;
        }
        else if (row2.has(lowerWord[0])) {
            targetRow = row2;
        }
        else {
            targetRow = row3;
        }
        let canBeTyped = true;
        for (const char of lowerWord) {
            if (!targetRow.has(char)) {
                canBeTyped = false;
                break;
            }
        }
        if (canBeTyped) {
            result.push(word);
        }
    }

    return result;
};