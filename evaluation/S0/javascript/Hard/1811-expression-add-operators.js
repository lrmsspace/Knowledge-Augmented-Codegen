// Source: https://leetcode.com/problems/expression-add-operators/   |   Difficulty: Hard
//
// Problem Description:
// Given a string num that contains only digits and an integer target, return all possibilities to insert the binary operators '+', '-', and/or '*' between the digits of num so that the resultant expression evaluates to the target value.
//
// Note that operands in the returned expressions should not contain leading zeros.
//
// Note that a number can contain multiple digits.
//
// Example:
// Input: num = "123", target = 6
// Output: ["1*2*3","1+2+3"]
// Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.
//
// Constraints:
// 1 <= num.length <= 10
// 	num consists of only digits.
// 	-231 <= target <= 231 - 1
//

/**
 * @param {string} num
 * @param {number} target
 * @return {string[]}
 */
var addOperators = function(num, target) {
    const res = [];
        
    const backtrack = (expr, pos, eval, multed) => {
        if (pos === num.length) {
            if (
                eval === target
            ) {
                res.push(expr);
            }
            return;
        }
        for (let i = pos; i < num.length; i++) {
            if (i !== pos && num[pos] === '0') {
                break; // Skip numbers with leading zeros
            }
            const cur = parseInt(num.substring(pos, i + 1));
            if (pos === 0) {
                backtrack(expr + cur, i + 1, cur, cur);
            }
            else {
                backtrack(expr + '+' + cur, i + 1, eval + cur, cur);
                backtrack(expr + '-' + cur, i + 1, eval - cur, -cur);
                backtrack(expr + '*' + cur, i + 1, eval - multed + multed * cur, multed * cur);
            }
        }
        };
        
            
};
