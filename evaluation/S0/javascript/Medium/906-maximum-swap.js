// Source: https://leetcode.com/problems/maximum-swap/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer num. You can swap two digits at most once to get the maximum valued number.
//
// Return the maximum valued number you can get.
//
// Example:
// Input: num = 2736
// Output: 7236
// Explanation: Swap the number 2 and the number 7.
//
// Constraints:
// 0 <= num <= 108
//

/**
 * @param {number} num
 * @return {number}
 */
var maximumSwap = function(num) {
    const digits = num.toString().split('').map(Number);
    const lastIndices = new Array(10).fill(-1);
    for (let i = 0; i < digits.length; i++) {
        lastIndices[digits[i]] = i;
    }
    for (let i = 0; i < digits.length; i++) {
        for (let d = 9; d > digits[i]; d--) {
            if (lastIndices[d] > i) {
                [digits[i], digits[lastIndices[d]]] = [digits[lastIndices[d]], digits[i]];
                return parseInt(digits.join(''), 10);
            }
        }
    }
    return num;
};  