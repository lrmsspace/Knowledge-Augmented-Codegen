// Source: https://leetcode.com/problems/score-of-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// Given a balanced parentheses string s, return the score of the string.
//
// The score of a balanced parentheses string is based on the following rule:
//
//
// 	"()" has score 1.
// 	AB has score A + B, where A and B are balanced parentheses strings.
// 	(A) has score 2 * A, where A is a balanced parentheses string.
//
// Example:
// Input: s = "()"
// Output: 1
//
// Constraints:
// 2 <= s.length <= 50
// 	s consists of only '(' and ')'.
// 	s is a balanced parentheses string.
//

/**
 * @param {string} s
 * @return {number}
 */
var scoreOfParentheses = function(s) {
    const stack = [];
    for (const char of s) {
        if (char === '(') {
            stack.push(0);
        }
        else {
            const v = stack.pop();
            const score = v === 0 ? 1 : 2 * v;
            if (stack.length > 0) {
                stack[stack.length - 1] += score;
            }
            else {
                stack.push(score);
            }
        }
    }
    return stack.pop(); 
};
