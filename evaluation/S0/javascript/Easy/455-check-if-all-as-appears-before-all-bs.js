// Source: https://leetcode.com/problems/check-if-all-as-appears-before-all-bs/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s consisting of only the characters 'a' and 'b', return true if every 'a' appears before every 'b' in the string. Otherwise, return false.
//
// Example:
// Input: s = "aaabbb"
// Output: true
// Explanation:
// The 'a's are at indices 0, 1, and 2, while the 'b's are at indices 3, 4, and 5.
// Hence, every 'a' appears before every 'b' and we return true.
//
// Constraints:
// 1 <= s.length <= 100
// 	s[i] is either 'a' or 'b'.
//

/**
 * @param {string} s
 * @return {boolean}
 */
var checkString = function(s) {
    const firstBIndex = s.indexOf('b');
    const lastAIndex = s.lastIndexOf('a');
    return firstBIndex === -1 || lastAIndex === -1 || firstBIndex > lastAIndex; 
};
