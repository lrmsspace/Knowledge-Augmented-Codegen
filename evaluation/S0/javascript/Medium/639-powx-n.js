// Source: https://leetcode.com/problems/powx-n/   |   Difficulty: Medium
//
// Problem Description:
// Implement pow(x, n), which calculates x raised to the power n (i.e., xn).
//
// Example:
// Input: x = 2.00000, n = 10
// Output: 1024.00000
//
// Constraints:
// -100.0 < x < 100.0
// 	-231 <= n <= 231-1
// 	n is an integer.
// 	Either x is not zero or n > 0.
// 	-104 <= xn <= 104
//

/**
 * @param {number} x
 * @param {number} n
 * @return {number}
 */
var myPow = function(x, n) {
    if (n === 0) return 1;
    if (n < 0) {
        x = 1 / x;
        n = -n;
    }
    let result = 1;
    while (n > 0) {
        if (n % 2 === 1) {
            result *= x;
        }
        x *= x;
        n = Math.floor(n / 2);
    }
    return result;
};