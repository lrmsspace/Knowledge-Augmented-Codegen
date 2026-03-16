// Source: https://leetcode.com/problems/rotate-string/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.
//
// A shift on s consists of moving the leftmost character of s to the rightmost position.
//
//
// 	For example, if s = "abcde", then it will be "bcdea" after one shift.
//
// Example:
// Input: s = "abcde", goal = "cdeab"
// Output: true
//
// Constraints:
// 1 <= s.length, goal.length <= 100
// 	s and goal consist of lowercase English letters.
//

/**
 * @param {string} s
 * @param {string} goal
 * @return {boolean}
 */
var rotateString = function(s, goal) {
    if (s.length !== goal.length) {
        return false;
    }
    const doubled = s + s;
    return doubled.includes(goal);
};
