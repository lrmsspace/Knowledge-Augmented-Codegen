// Source: https://leetcode.com/problems/basic-calculator/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s representing a valid expression, implement a basic calculator to evaluate it, and return the result of the evaluation.
//
// Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().
//
// Example:
// Input: s = "1 + 1"
// Output: 2
//
// Constraints:
// 1 <= s.length <= 3 * 105
// 	s consists of digits, '+', '-', '(', ')', and ' '.
// 	s represents a valid expression.
// 	'+' is not used as a unary operation (i.e., "+1" and "+(2 + 3)" is invalid).
// 	'-' could be used as a unary operation (i.e., "-1" and "-(2 + 3)" is valid).
// 	There will be no two consecutive operators in the input.
// 	Every number and running calculation will fit in a signed 32-bit integer.
//

/**
 * @param {string} s
 * @return {number}
 */
var calculate = function(s) {
    


    let stack = [];
    let sign = 1;
    let result = 0;
    for (let i = 0; i < s.length; i++) {
        let char = s[i];
        if (char === ' ') {
            continue;
        } else if (char === '+') {
            sign = 1;
        } else if (char === '-') {
            sign = -1;
        } else if (char === '(') {
            stack.push(result);
            stack.push(sign);
            result = 0;
            sign = 1;
        } else if (char === ')') {
            result *= stack.pop();
            result += stack.pop();
        } else {
            let num = 0;
            while (i < s.length && s[i] >= '0' && s[i] <= '9') {
                num = num * 10 + (s[i] - '0');
                i++;
            }
            i--;
            result += sign * num;
        }
    }
    return result;
            
};
