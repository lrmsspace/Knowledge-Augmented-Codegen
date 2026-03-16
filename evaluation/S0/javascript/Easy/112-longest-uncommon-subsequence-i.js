// Source: https://leetcode.com/problems/longest-uncommon-subsequence-i/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings a and b, return the length of the longest uncommon subsequence between a and b. If no such uncommon subsequence exists, return -1.
//
// An uncommon subsequence between two strings is a string that is a subsequence of exactly one of them.
//
// Example:
// Input: a = "aba", b = "cdc"
// Output: 3
// Explanation: One longest uncommon subsequence is "aba" because "aba" is a subsequence of "aba" but not "cdc".
// Note that "cdc" is also a longest uncommon subsequence.
//
// Constraints:
// 1 <= a.length, b.length <= 100
// 	a and b consist of lower-case English letters.
//

/**
 * @param {string} a
 * @param {string} b
 * @return {number}
 */
var findLUSlength = function(a, b) {
    if (a === b) {
        return -1;
    }
    return Math.max(a.length, b.length);            
};
