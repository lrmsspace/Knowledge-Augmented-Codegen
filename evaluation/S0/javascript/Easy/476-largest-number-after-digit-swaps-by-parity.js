// Source: https://leetcode.com/problems/largest-number-after-digit-swaps-by-parity/   |   Difficulty: Easy
//
// Problem Description:
// You are given a positive integer num. You may swap any two digits of num that have the same parity (i.e. both odd digits or both even digits).
//
// Return the largest possible value of num after any number of swaps.
//
// Example:
// Input: num = 1234
// Output: 3412
// Explanation: Swap the digit 3 with the digit 1, this results in the number 3214.
// Swap the digit 2 with the digit 4, this results in the number 3412.
// Note that there may be other sequences of swaps but it can be shown that 3412 is the largest possible number.
// Also note that we may not swap the digit 4 with the digit 1 since they are of different parities.
//
// Constraints:
// 1 <= num <= 109
//

/**
 * @param {number} num
 * @return {number}
 */
var largestInteger = function(num) {
    const digits = String(num).split('').map(Number);
    const evenDigits = digits.filter(d => d % 2 === 0).sort((a, b) => b - a);
    const oddDigits = digits.filter(d => d % 2 !== 0).sort((a, b) => b - a);
    let evenIndex = 0;
    let oddIndex = 0;
    const result = digits.map(d => {
        if (d % 2 === 0) {
            return evenDigits[evenIndex++];
        } else {
            return oddDigits[oddIndex++];
        }
    });
    return Number(result.join(''));
};