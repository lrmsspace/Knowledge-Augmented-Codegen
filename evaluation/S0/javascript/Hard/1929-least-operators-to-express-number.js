// Source: https://leetcode.com/problems/least-operators-to-express-number/   |   Difficulty: Hard
//
// Problem Description:
// Given a single positive integer x, we will write an expression of the form x (op1) x (op2) x (op3) x ... where each operator op1, op2, etc. is either addition, subtraction, multiplication, or division (+, -, *, or /). For example, with x = 3, we might write 3 * 3 / 3 + 3 - 3 which is a value of 3.
//
// When writing such an expression, we adhere to the following conventions:
//
//
// 	The division operator (/) returns rational numbers.
// 	There are no parentheses placed anywhere.
// 	We use the usual order of operations: multiplication and division happen before addition and subtraction.
// 	It is not allowed to use the unary negation operator (-). For example, "x - x" is a valid expression as it only uses subtraction, but "-x + x" is not because it uses negation.
//
//
// We would like to write an expression with the least number of operators such that the expression equals the given target. Return the least number of operators used.
//
// Example:
// Input: x = 3, target = 19
// Output: 5
// Explanation: 3 * 3 + 3 * 3 + 3 / 3.
// The expression contains 5 operations.
//
// Constraints:
// 2 <= x <= 100
// 	1 <= target <= 2 * 108
//

/**
 * @param {number} x
 * @param {number} target
 * @return {number}
 */
var leastOpsExpressTarget = function(x, target) {
    if (target === 0) return 0;
    if (target === 1) return 1;
    const dp = new Map();
    function helper(target) {
        if (dp.has(target)) return dp.get(target);
        if (target < x) {
            dp.set(target, Math.min(2 * target - 1, 2 * (x - target) - 1));
            return dp.get(target);
        }
        let n = Math.floor(Math.log(target) / Math.log(x));
        let remainder = target - Math.pow(x, n);
        let result = n + helper(remainder);
        if (remainder > 0) {
            result = Math.min(result, n + 1 + helper(Math.pow(x, n + 1) - target));
        }
        dp.set(target, result);
        return result;
    }
    return helper(target);  
};
