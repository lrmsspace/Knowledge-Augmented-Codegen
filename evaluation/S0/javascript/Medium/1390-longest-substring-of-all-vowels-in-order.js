// Source: https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/   |   Difficulty: Medium
//
// Problem Description:
// A string is considered beautiful if it satisfies the following conditions:
//
//
// 	Each of the 5 English vowels ('a', 'e', 'i', 'o', 'u') must appear at least once in it.
// 	The letters must be sorted in alphabetical order (i.e. all 'a's before 'e's, all 'e's before 'i's, etc.).
//
//
// For example, strings "aeiou" and "aaaaaaeiiiioou" are considered beautiful, but "uaeio", "aeoiu", and "aaaeeeooo" are not beautiful.
//
// Given a string word consisting of English vowels, return the length of the longest beautiful substring of word. If no such substring exists, return 0.
//
// A substring is a contiguous sequence of characters in a string.
//
// Example:
// Input: word = "aeiaaioaaaaeiiiiouuuooaauuaeiu"
// Output: 13
// Explanation: The longest beautiful substring in word is "aaaaeiiiiouuu" of length 13.
//
// Constraints:
// 1 <= word.length <= 5 * 105
// 	word consists of characters 'a', 'e', 'i', 'o', and 'u'.
//

/**
 * @param {string} word
 * @return {number}
 */
var longestBeautifulSubstring = function(word) {
    const vowels = ['a', 'e', 'i', 'o', 'u'];
    let maxLength = 0;
    let left = 0;
    let count = 0;
    for (let right = 0; right < word.length; right++) {
        if (right > 0 && word[right] < word[right - 1]) {
            left = right;
            count = 1;
        } else if (right === 0 || word[right] > word[right - 1]) {
            count++;
        }
        if (count === 5) {
            maxLength = Math.max(maxLength, right - left + 1);
        }
    }
    return maxLength;
};