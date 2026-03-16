// Source: https://leetcode.com/problems/count-substrings-starting-and-ending-with-given-character/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s and a character c. Return the total number of substrings of s that start and end with c.
//
// Example:
// Input: s = "abada", c = "a"
//
// Output: 6
//
// Explanation: Substrings starting and ending with "a" are: "abada", "abada", "abada", "abada", "abada", "abada".
//
// Constraints:
// 1 <= s.length <= 105
// 	s and c consist only of lowercase English letters.
//

/**
 * @param {string} s
 * @param {character} c
 * @return {number}
 */
var countSubstrings = function(s, c) {
    let countC = 0;
    for (const char of s) {
        if (char === c) {
            countC++;
        }
    }
    return (countC * (countC + 1)) / 2;
};
