// Source: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s of '(' , ')' and lowercase English characters.
//
// Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.
//
// Formally, a parentheses string is valid if and only if:
//
//
// 	It is the empty string, contains only lowercase characters, or
// 	It can be written as AB (A concatenated with B), where A and B are valid strings, or
// 	It can be written as (A), where A is a valid string.
//
// Example:
// Input: s = "lee(t(c)o)de)"
// Output: "lee(t(c)o)de"
// Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '(' , ')', or lowercase English letter.
//

/**
 * @param {string} s
 * @return {string}
 */
var minRemoveToMakeValid = function(s) {
    const sArr = s.split('');
    const stack = [];
    for (let i = 0; i < sArr.length; i++) {
        if (sArr[i] === '(') {
            stack.push(i);
        } else if (sArr[i] === ')') {
            if (stack.length > 0) {
                stack.pop();
            } else {
                sArr[i] = '';
            }
        }
    }
    while (stack.length > 0) {
        const index = stack.pop();
        sArr[index] = '';
    }
    return sArr.join('');
        
};
