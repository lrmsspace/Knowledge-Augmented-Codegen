// Source: https://leetcode.com/problems/rearrange-spaces-between-words/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string text of words that are placed among some number of spaces. Each word consists of one or more lowercase English letters and are separated by at least one space. It's guaranteed that text contains at least one word.
//
// Rearrange the spaces so that there is an equal number of spaces between every pair of adjacent words and that number is maximized. If you cannot redistribute all the spaces equally, place the extra spaces at the end, meaning the returned string should be the same length as text.
//
// Return the string after rearranging the spaces.
//
// Example:
// Input: text = "  this   is  a sentence "
// Output: "this   is   a   sentence"
// Explanation: There are a total of 9 spaces and 4 words. We can evenly divide the 9 spaces between the words: 9 / (4-1) = 3 spaces.
//
// Constraints:
// 1 <= text.length <= 100
// 	text consists of lowercase English letters and ' '.
// 	text contains at least one word.
//

/**
 * @param {string} text
 * @return {string}
 */
var reorderSpaces = function(text) {
    const words = text.trim().split(/\s+/);
    const totalSpaces = text.length - words.reduce((acc, word) => acc + word.length, 0);
    const gaps = words.length - 1;
    let spaceBetween = 0;
    let extraSpaces = totalSpaces;
    if (gaps > 0) {
        spaceBetween = Math.floor(totalSpaces / gaps);
        extraSpaces = totalSpaces % gaps;
    }
    return words.join(' '.repeat(spaceBetween)) + ' '.repeat(extraSpaces);
};
