// Source: https://leetcode.com/problems/ugly-number-iii/   |   Difficulty: Medium
//
// Problem Description:
// An ugly number is a positive integer that is divisible by a, b, or c.
//
// Given four integers n, a, b, and c, return the nth ugly number.
//
// Example:
// Input: n = 3, a = 2, b = 3, c = 5
// Output: 4
// Explanation: The ugly numbers are 2, 3, 4, 5, 6, 8, 9, 10... The 3rd is 4.
//
// Constraints:
// 1 <= n, a, b, c <= 109
// 	1 <= a * b * c <= 1018
// 	It is guaranteed that the result will be in range [1, 2 * 109].
//

/**
 * @param {number} n
 * @param {number} a
 * @param {number} b
 * @param {number} c
 * @return {number}
 */
var nthUglyNumber = function(n, a, b, c) {
    const gcd = (x, y) => {
        while (y) {
            [x, y] = [y, x % y];
        }
        return x;
    };

    const lcm = (x, y) => (x * y) / gcd(x, y);
    const countUglyNumbers = (x) => {
        return Math.floor(x / a) + Math.floor(x / b) + Math.floor(x / c)
             - Math.floor(x / lcm(a, b)) - Math.floor(x / lcm(b, c)) - Math.floor(x / lcm(c, a))
             + Math.floor(x / lcm(a, lcm(b, c)));
    }
    let left = 1, right = 2 * 1e9;
    let result = -1;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        if (countUglyNumbers(mid) >= n) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;  
            
};
