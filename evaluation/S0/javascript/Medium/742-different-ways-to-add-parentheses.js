// Source: https://leetcode.com/problems/different-ways-to-add-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// Given a string expression of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. You may return the answer in any order.
//
// The test cases are generated such that the output values fit in a 32-bit integer and the number of different results does not exceed 104.
//
// Example:
// Input: expression = "2-1-1"
// Output: [0,2]
// Explanation:
// ((2-1)-1) = 0 
// (2-(1-1)) = 2
//
// Constraints:
// 1 <= expression.length <= 20
// 	expression consists of digits and the operator '+', '-', and '*'.
// 	All the integer values in the input expression are in the range [0, 99].
// 	The integer values in the input expression do not have a leading '-' or '+' denoting the sign.
//

/**
 * @param {string} expression
 * @return {number[]}
 */
var diffWaysToCompute = function(expression) {
    const memo = new Map();

    function computeWays(expr) {
        if (memo.has(expr)) {
            return memo.get(expr);
        }
        const results = [];
        for (let i = 0; i < expr.length; i++) {
            const char = expr[i];
            if (char === '+' || char === '-' || char === '*') {
                const leftPart = expr.substring(0, i);
                const rightPart = expr.substring(i + 1);
                const leftResults = computeWays(leftPart);
                const rightResults = computeWays(rightPart);
                for (const left of leftResults) {
                    for (const right of rightResults) {
                        let computed;
                        if (char === '+') {
                            computed = left + right;
                        }
                        else if (char === '-') {
                            computed = left - right;
                        }
                        else if (char === '*') {
                            computed = left * right;
                        }
                        results.push(computed);
                    }
                }
            }
        }
        if (results.length === 0) {
            results.push(parseInt(expr, 10));
        }
        memo.set(expr, results);
        return results;
    }
    return computeWays(expression); 
};
