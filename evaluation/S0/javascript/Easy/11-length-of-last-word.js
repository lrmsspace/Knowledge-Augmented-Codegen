// Source: https://leetcode.com/problems/length-of-last-word/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s consisting of words and spaces, return the length of the last word in the string.
//
// A word is a maximal substring consisting of non-space characters only.
//
// Example:
// Input: s = "Hello World"
// Output: 5
// Explanation: The last word is "World" with length 5.
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of only English letters and spaces ' '.
// 	There will be at least one word in s.
//

/**
 * @param {string} s
 * @return {number}
 */
var lengthOfLastWord = function(s) {
    // Trim any trailing spaces from the string
    s = s.trim();
    // Split the string into words based on spaces
    const words = s.split(' ');
    // Return the length of the last word
    return words[words.length - 1].length;          
};
