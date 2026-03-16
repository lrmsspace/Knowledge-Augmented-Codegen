// Source: https://leetcode.com/problems/basic-calculator-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s which represents an expression, evaluate this expression and return its value. 
//
// The integer division should truncate toward zero.
//
// You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].
//
// Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().
//
// Example:
// Input: s = "3+2*2"
// Output: 7
//
// Constraints:
// 1 <= s.length <= 3 * 105
// 	s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
// 	s represents a valid expression.
// 	All the integers in the expression are non-negative integers in the range [0, 231 - 1].
// 	The answer is guaranteed to fit in a 32-bit integer.
//

/**
 * @param {string} s
 * @return {number}
 */
var calculate = function(s) {
    const stack = [];
    let currentNumber = 0;
    let operation = '+';

    for (let i = 0; i < s.length; i++) {
        const char = s[i];
        if (!isNaN(char) && char !== ' ') {
            currentNumber = currentNumber * 10 + parseInt(char, 10);
        }
        if (isNaN(char) && char !== ' ' || i === s.length - 1) {
            if (operation === '+') {
                stack.push(currentNumber);
            } else if (operation === '-') {
                stack.push(-currentNumber);
            } else if (operation === '*') {
                stack.push(stack.pop() * currentNumber);
            } else if (operation === '/') {
                const top = stack.pop();
                stack.push(top < 0 ? Math.ceil(top / currentNumber) : Math.floor(top / currentNumber));
            }
            operation = char;
            currentNumber = 0;
        }
    }

    return stack.reduce((acc, num) => acc + num, 0);    
};
