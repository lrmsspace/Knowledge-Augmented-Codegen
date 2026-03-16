// Source: https://leetcode.com/problems/split-a-string-in-balanced-strings/   |   Difficulty: Easy
//
// Problem Description:
// Balanced strings are those that have an equal quantity of 'L' and 'R' characters.
//
// Given a balanced string s, split it into some number of substrings such that:
//
//
// 	Each substring is balanced.
//
//
// Return the maximum number of balanced strings you can obtain.
//
// Example:
// Input: s = "RLRRLLRLRL"
// Output: 4
// Explanation: s can be split into "RL", "RRLL", "RL", "RL", each substring contains same number of 'L' and 'R'.
//
// Constraints:
// 2 <= s.length <= 1000
// 	s[i] is either 'L' or 'R'.
// 	s is a balanced string.
//

/**
 * @param {string} s
 * @return {number}
 */
var balancedStringSplit = function(s) {
    let balance = 0;
    let count = 0;
    for (const char of s) {
        if (char === 'L') {
            balance++;
        } else {
            balance--;
        }
        if (balance === 0) {
            count++;
        }
    }
    return count;
};