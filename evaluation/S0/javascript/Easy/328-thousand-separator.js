// Source: https://leetcode.com/problems/thousand-separator/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, add a dot (".") as the thousands separator and return it in string format.
//
// Example:
// Input: n = 987
// Output: "987"
//
// Constraints:
// 0 <= n <= 231 - 1
//

/**
 * @param {number} n
 * @return {string}
 */
var thousandSeparator = function(n) {
    const numStr = n.toString();
    let result = '';
    let count = 0;
    for (let i = numStr.length - 1; i >= 0; i--) {
        result = numStr[i] + result;
        count++;
        if (count === 3 && i !== 0) {
            result = '.' + result;
            count = 0;
        }
    }
    return result;
};