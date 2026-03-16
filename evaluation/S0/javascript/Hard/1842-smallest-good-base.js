// Source: https://leetcode.com/problems/smallest-good-base/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n represented as a string, return the smallest good base of n.
//
// We call k >= 2 a good base of n, if all digits of n base k are 1's.
//
// Example:
// Input: n = "13"
// Output: "3"
// Explanation: 13 base 3 is 111.
//
// Constraints:
// n is an integer in the range [3, 1018].
// 	n does not contain any leading zeros.
//

/**
 * @param {string} n
 * @return {string}
 */
var smallestGoodBase = function(n) {
    const num = BigInt(n);
    for (let m = 63; m >= 1; m--) {
        const k = BigInt(Math.floor(Math.pow(Number(num), 1 / m)));
        let sum = 1n, current = 1n;
        for (let i = 1; i <= m; i++) {
            current *= k;
            sum += current;
        }
        if (sum === num) {
            return k.toString();
        }
    }
    return (num - 1n).toString();   
};
