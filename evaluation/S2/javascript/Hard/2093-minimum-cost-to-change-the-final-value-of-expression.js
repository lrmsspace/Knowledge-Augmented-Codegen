// Source: https://leetcode.com/problems/minimum-cost-to-change-the-final-value-of-expression/   |   Difficulty: Hard
//
// Problem Description:
// You are given a valid boolean expression as a string expression consisting of the characters '1','0','&' (bitwise AND operator),'|' (bitwise OR operator),'(', and ')'.
//
//
// 	For example, "()1|1" and "(1)&()" are not valid while "1", "(((1))|(0))", and "1|(0&(1))" are valid expressions.
//
//
// Return the minimum cost to change the final value of the expression.
//
//
// 	For example, if expression = "1|1|(0&0)&1", its value is 1|1|(0&0)&1 = 1|1|0&1 = 1|0&1 = 1&1 = 1. We want to apply operations so that the new expression evaluates to 0.
//
//
// The cost of changing the final value of an expression is the number of operations performed on the expression. The types of operations are described as follows:
//
//
// 	Turn a '1' into a '0'.
// 	Turn a '0' into a '1'.
// 	Turn a '&' into a '|'.
// 	Turn a '|' into a '&'.
//
//
// Note: '&' does not take precedence over '|' in the order of calculation. Evaluate parentheses first, then in left-to-right order.
//
// Example:
// Input: expression = "1&(0|1)"
// Output: 1
// Explanation: We can turn "1&(0|1)" into "1&(0&1)" by changing the '|' to a '&' using 1 operation.
// The new expression evaluates to 0.
//
// Constraints:
// 1 <= expression.length <= 105
// 	expression only contains '1','0','&','|','(', and ')'
// 	All parentheses are properly matched.
// 	There will be no empty parentheses (i.e: "()" is not a substring of expression).
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} expression
 * @return {number}
 */
var minOperationsToFlip = function(expression) {
    const stack = [];
    
    for (const char of expression) {
        if (char === ')') {
            const subExpr = [];
            while (stack.length > 0 && stack[stack.length - 1] !== '(') {
                subExpr.unshift(stack.pop());
            }
            stack.pop(); // Remove '('
            stack.push(evaluate(subExpr));
        } else {
            stack.push(char);
        }
    }
    
    return evaluate(stack);
};
