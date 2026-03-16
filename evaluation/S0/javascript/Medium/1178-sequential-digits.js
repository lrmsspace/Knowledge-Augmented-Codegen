// Source: https://leetcode.com/problems/sequential-digits/   |   Difficulty: Medium
//
// Problem Description:
// An integer has sequential digits if and only if each digit in the number is one more than the previous digit.
//
// Return a sorted list of all the integers in the range [low, high] inclusive that have sequential digits.
//
// Example:
// Input: low = 100, high = 300
// Output: [123,234]
//
// Constraints:
// 10 <= low <= high <= 10^9
//

/**
 * @param {number} low
 * @param {number} high
 * @return {number[]}
 */
var sequentialDigits = function(low, high) {
    const result = [];
    const digits = '123456789';
    const lowLength = low.toString().length;
    const highLength = high.toString().length;
    for (let length = lowLength; length <= highLength; length++) {
        for (let start = 0; start <= 9 - length; start++) {
            const num = parseInt(digits.substr(start, length));
            if (num >= low && num <= high) {
                result.push(num);
            }
        }
    }
    return result;
        
};
