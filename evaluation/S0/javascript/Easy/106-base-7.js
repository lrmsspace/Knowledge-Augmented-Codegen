// Source: https://leetcode.com/problems/base-7/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer num, return a string of its base 7 representation.
//
// Example:
// Input: num = 100
// Output: "202"
//
// Constraints:
// -107 <= num <= 107
//

/**
 * @param {number} num
 * @return {string}
 */
var convertToBase7 = function(num) {
    if (num === 0) return "0";
    const isNegative = num < 0;
    num = Math.abs(num);
    let result = '';
    while (num > 0) {
        result = (num % 7) + result;
        num = Math.floor(num / 7);
    }
    return isNegative ? '-' + result : result;          
};
