// Source: https://leetcode.com/problems/number-of-digit-one/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, count the total number of digit 1 appearing in all non-negative integers less than or equal to n.
//
// Example:
// Input: n = 13
// Output: 6
//
// Constraints:
// 0 <= n <= 109
//

/**
 * @param {number} n
 * @return {number}
 */
var countDigitOne = function(n) {
    let count = 0;
    for (let i = 1; i <= n; i *= 10) {
        const divider = i * 10;
        const left = Math.floor(n / divider);
        const current = Math.floor((n % divider) / i);
        const right = n % i;
        count += left * i;
        if (current > 1) {
            count += i;
        } else if (current === 1) {
            count += right + 1;
        }
    }
    return count;
        
};
