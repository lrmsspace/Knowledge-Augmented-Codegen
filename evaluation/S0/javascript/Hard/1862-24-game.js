// Source: https://leetcode.com/problems/24-game/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array cards of length 4. You have four cards, each containing a number in the range [1, 9]. You should arrange the numbers on these cards in a mathematical expression using the operators ['+', '-', '*', '/'] and the parentheses '(' and ')' to get the value 24.
//
// You are restricted with the following rules:
//
//
// 	The division operator '/' represents real division, not integer division.
//
// 	
// 		For example, 4 / (1 - 2 / 3) = 4 / (1 / 3) = 12.
// 	
// 	
// 	Every operation done is between two numbers. In particular, we cannot use '-' as a unary operator.
// 	
// 		For example, if cards = [1, 1, 1, 1], the expression "-1 - 1 - 1 - 1" is not allowed.
// 	
// 	
// 	You cannot concatenate numbers together
// 	
// 		For example, if cards = [1, 2, 1, 2], the expression "12 + 12" is not valid.
// 	
// 	
//
//
// Return true if you can get such expression that evaluates to 24, and false otherwise.
//
// Example:
// Input: cards = [4,1,8,7]
// Output: true
// Explanation: (8-4) * (7-1) = 24
//
// Constraints:
// cards.length == 4
// 	1 <= cards[i] <= 9
//

/**
 * @param {number[]} cards
 * @return {boolean}
 */
var judgePoint24 = function(cards) {
    


    let EPSILON = 1e-6;
    let TARGET = 24;

    function solve(nums) {
        if (nums.length === 1) {
            return Math.abs(nums[0] - TARGET) < EPSILON;
        }
        for (let i = 0; i < nums.length; i++) {
            for (let j = 0; j < nums.length; j++) {
                if (i !== j) {
                    let nextNums = [];
                    for (let k = 0; k < nums.length; k++) {
                        if (k !== i && k !== j) {
                            nextNums.push(nums[k]);
                        }
                    }
                    for (let op of ['+', '-', '*', '/']) {
                        if ((op === '+' || op === '*') && i > j) {
                            continue; // Skip duplicate operations
                        }
                        if (op === '/' && Math.abs(nums[j]) < EPSILON) {
                            continue; // Skip division by zero
                        }
                        let result;
                        switch (op) {
                            case '+':
                                result = nums[i] + nums[j];
                                break;
                            case '-':
                                result = nums[i] - nums[j];
                                break;
                            case '*':
                                result = nums[i] * nums[j];
                                break;
                            case '/':
                                result = nums[i] / nums[j];
                                break;
                        }
                        nextNums.push(result);
                        if (solve(nextNums)) {
                            return true;
                        }
                        nextNums.pop();
                    }
                }
            }
        }
        return false;
    }
    return solve(cards);    
};
