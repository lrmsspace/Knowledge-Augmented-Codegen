// Source: https://leetcode.com/problems/valid-parenthesis-string/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s containing only three types of characters: '(', ')' and '*', return true if s is valid.
//
// The following rules define a valid string:
//
//
// 	Any left parenthesis '(' must have a corresponding right parenthesis ')'.
// 	Any right parenthesis ')' must have a corresponding left parenthesis '('.
// 	Left parenthesis '(' must go before the corresponding right parenthesis ')'.
// 	'*' could be treated as a single right parenthesis ')' or a single left parenthesis '(' or an empty string "".
//
// Example:
// Input: s = "()"
// Output: true
//
// Constraints:
// 1 <= s.length <= 100
// 	s[i] is '(', ')' or '*'.
//

/**
 * @param {string} s
 * @return {boolean}
 */
var checkValidString = function(s) {
    let low = 0;  // Minimum number of open parentheses
    let high = 0; // Maximum number of open parentheses

    for (const char of s) {
        if (char === '(') {
            low++;
            high++;
        } else if (char === ')') {
            low = Math.max(low - 1, 0);
            high--;
        } else { // char === '*'
            low = Math.max(low - 1, 0);
            high++;
        }
        if (high < 0) {
            return false;
        }
    }
    return low === 0;
};  