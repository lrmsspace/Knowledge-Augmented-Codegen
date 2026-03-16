// Source: https://leetcode.com/problems/substring-matching-pattern/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string s and a pattern string p, where p contains exactly one '*' character.
//
// The '*' in p can be replaced with any sequence of zero or more characters.
//
// Return true if p can be made a substring of s, and false otherwise.
//
// Example:
// Input: s = "leetcode", p = "ee*e"
//
// Output: true
//
// Explanation:
//
// By replacing the '*' with "tcod", the substring "eetcode" matches the pattern.
//
// Constraints:
// 1 <= s.length <= 50
// 	1 <= p.length <= 50 
// 	s contains only lowercase English letters.
// 	p contains only lowercase English letters and exactly one '*'
//

/**
 * @param {string} s
 * @param {string} p
 * @return {boolean}
 */
var hasMatch = function(s, p) {
    const [prefix, suffix] = p.split('*');
    if (s.length < prefix.length + suffix.length) {
        return false;
    }
    return s.startsWith(prefix) && s.endsWith(suffix);
};
