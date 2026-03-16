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

/**
 * @param {string} expression
 * @return {number}
 */
var minOperationsToFlip = function(expression) {
        const evaluate = (expr) => {
        const stack = [];
        for (const char of expr) {
            if (char === '0' || char === '1') {
                stack.push([char, 0]);
            }
            else if (char === '&' || char === '|') {
                stack.push(char);
            }
            else if (char === ')') {
                const operands = [];
                while (stack.length > 0 && stack[stack.length - 1] !== '(') {
                    operands.push(stack.pop());
                }
                stack.pop();
                const [val1, cost1] = operands.pop();
                const operator = operands.pop();
                const [val2, cost2] = operands.pop();
                let newVal, newCost;
                if (operator === '&') {
                    newVal = (val1 === '1' && val2 === '1') ? '1' : '0';
                    newCost = (newVal === '1') ? Math.min(cost1 + 1, cost2 + 1) : Math.min(cost1, cost2);
                }
                else {
                    newVal = (val1 === '0' && val2 === '0') ? '0' : '1';
                    newCost = (newVal === '0') ? Math.min(cost1 + 1, cost2 + 1) : Math.min(cost1, cost2);
                }
                stack.push([newVal, newCost]);
            }
        }        return stack.pop();
    }
    const [finalValue, minCost] = evaluate(expression);
    return minCost;
};
