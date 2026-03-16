// Source: https://leetcode.com/problems/split-strings-by-separator/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of strings words and a character separator, split each string in words by separator.
//
// Return an array of strings containing the new strings formed after the splits, excluding empty strings.
//
// Notes
//
//
// 	separator is used to determine where the split should occur, but it is not included as part of the resulting strings.
// 	A split may result in more than two strings.
// 	The resulting strings must maintain the same order as they were initially given.
//
// Example:
// Input: words = ["one.two.three","four.five","six"], separator = "."
// Output: ["one","two","three","four","five","six"]
// Explanation: In this example we split as follows:
//
// "one.two.three" splits into "one", "two", "three"
// "four.five" splits into "four", "five"
// "six" splits into "six" 
//
// Hence, the resulting array is ["one","two","three","four","five","six"].
//
// Constraints:
// 1 <= words.length <= 100
// 	1 <= words[i].length <= 20
// 	characters in words[i] are either lowercase English letters or characters from the string ".,|$#@" (excluding the quotes)
// 	separator is a character from the string ".,|$#@" (excluding the quotes)
//

/**
 * @param {string[]} words
 * @param {character} separator
 * @return {string[]}
 */
var splitWordsBySeparator = function(words, separator) {
    const result = [];
    for (const word of words) {
        const splitWords = word.split(separator);
        for (const splitWord of splitWords) {
            if (splitWord !== '') {
                result.push(splitWord);
            }
        }
    }
    return result;
};
