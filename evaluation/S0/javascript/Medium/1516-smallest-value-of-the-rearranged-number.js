// Source: https://leetcode.com/problems/smallest-value-of-the-rearranged-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer num. Rearrange the digits of num such that its value is minimized and it does not contain any leading zeros.
//
// Return the rearranged number with minimal value.
//
// Note that the sign of the number does not change after rearranging the digits.
//
// Example:
// Input: num = 310
// Output: 103
// Explanation: The possible arrangements for the digits of 310 are 013, 031, 103, 130, 301, 310. 
// The arrangement with the smallest value that does not contain any leading zeros is 103.
//
// Constraints:
// -1015 <= num <= 1015
//

/**
 * @param {number} num
 * @return {number}
 */
var smallestNumber = function(num) {
    if (num === 0) return 0;
    const isNegative = num < 0;
    const digits = Math.abs(num).toString().split('');
    if (isNegative) {
        digits.sort((a, b) => b - a);
        return -parseInt(digits.join(''));
    } else {
        digits.sort((a, b) => a - b);
        if (digits[0] === '0') {
            let i = 1;
            while (i < digits.length && digits[i] === '0') {
                i++;
            }
            if (i < digits.length) {
                [digits[0], digits[i]] = [digits[i], digits[0]];
            }
        }
        return parseInt(digits.join(''));
    }
};