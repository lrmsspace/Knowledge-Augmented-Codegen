// Source: https://leetcode.com/problems/parsing-a-boolean-expression/   |   Difficulty: Hard
//
// Problem Description:
// A boolean expression is an expression that evaluates to either true or false. It can be in one of the following shapes:
//
//
// 	't' that evaluates to true.
// 	'f' that evaluates to false.
// 	'!(subExpr)' that evaluates to the logical NOT of the inner expression subExpr.
// 	'&(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical AND of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
// 	'|(subExpr1, subExpr2, ..., subExprn)' that evaluates to the logical OR of the inner expressions subExpr1, subExpr2, ..., subExprn where n >= 1.
//
//
// Given a string expression that represents a boolean expression, return the evaluation of that expression.
//
// It is guaranteed that the given expression is valid and follows the given rules.
//
// Example:
// Input: expression = "&(|(f))"
// Output: false
// Explanation: 
// First, evaluate |(f) --> f. The expression is now "&(f)".
// Then, evaluate &(f) --> f. The expression is now "f".
// Finally, return false.
//
// Constraints:
// 1 <= expression.length <= 2 * 104
// 	expression[i] is one following characters: '(', ')', '&', '|', '!', 't', 'f', and ','.
//

/**
 * @param {string} expression
 * @return {boolean}
 */
var parseBoolExpr = function(expression) {
    const stack = [];
    for (const char of expression) {
        if (char === ')') {
            const subExpr = [];
            while (stack.length > 0 && stack[stack.length - 1] !== '(') {
                subExpr.push(stack.pop());
            }
            stack.pop(); // Remove the '('
            const operator = stack.pop();
            let result;
            if (operator === '!') {
                result = subExpr[0] === 't' ? 'f' : 't';
            }
            else if (operator === '&') {
                result = 't';
                for (const val of subExpr) {
                    if (val === 'f') {
                        result = 'f';
                        break;
                    }
                }
            }
            else if (operator === '|') {
                result = 'f';
                for (const val of subExpr) {
                    if (val === 't') {
                        result = 't';
                        break;
                    }
                }
            }
            stack.push(result);
        }
        else if (char !== ',') {
            stack.push(char);
        }
    }
    return stack[0] === 't';    
};
