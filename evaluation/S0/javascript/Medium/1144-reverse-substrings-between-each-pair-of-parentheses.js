// Source: https://leetcode.com/problems/reverse-substrings-between-each-pair-of-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s that consists of lower case English letters and brackets.
//
// Reverse the strings in each pair of matching parentheses, starting from the innermost one.
//
// Your result should not contain any brackets.
//
// Example:
// Input: s = "(abcd)"
// Output: "dcba"
//
// Constraints:
// 1 <= s.length <= 2000
// 	s only contains lower case English characters and parentheses.
// 	It is guaranteed that all parentheses are balanced.
//

/**
 * @param {string} s
 * @return {string}
 */
var reverseParentheses = function(s) {
    const stack = [];
    let currentString = '';
    for (const char of s) {
        if (char === '(') {
            stack.push(currentString);
            currentString = '';
        } else if (char === ')') {
            currentString = currentString.split('').reverse().join('');
            currentString = stack.pop() + currentString;
        } else {
            currentString += char;
        }
    }
    return currentString;
        
};
