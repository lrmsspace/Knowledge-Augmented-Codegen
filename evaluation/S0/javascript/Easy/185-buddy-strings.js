// Source: https://leetcode.com/problems/buddy-strings/   |   Difficulty: Easy
//
// Problem Description:
// Given two strings s and goal, return true if you can swap two letters in s so the result is equal to goal, otherwise, return false.
//
// Swapping letters is defined as taking two indices i and j (0-indexed) such that i != j and swapping the characters at s[i] and s[j].
//
//
// 	For example, swapping at indices 0 and 2 in "abcd" results in "cbad".
//
// Example:
// Input: s = "ab", goal = "ba"
// Output: true
// Explanation: You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is equal to goal.
//
// Constraints:
// 1 <= s.length, goal.length <= 2 * 104
// 	s and goal consist of lowercase letters.
//

/**
 * @param {string} s
 * @param {string} goal
 * @return {boolean}
 */
var buddyStrings = function(s, goal) {
    if (s.length !== goal.length) return false;

    if (s === goal) {
        const seen = new Set();
        for (const char of s) {
            if (seen.has(char)) {
                return true;
            }
            seen.add(char);
        }
        return false;
    }

    const diff = [];
    for (let i = 0; i < s.length; i++) {
        if (s[i] !== goal[i]) {
            diff.push(i);
        }
    }

    return diff.length === 2 &&
           s[diff[0]] === goal[diff[1]] &&
           s[diff[1]] === goal[diff[0]];
};