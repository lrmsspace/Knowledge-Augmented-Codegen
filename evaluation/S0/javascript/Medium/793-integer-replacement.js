// Source: https://leetcode.com/problems/integer-replacement/   |   Difficulty: Medium
//
// Problem Description:
// Given a positive integer n, you can apply one of the following operations:
//
//
// 	If n is even, replace n with n / 2.
// 	If n is odd, replace n with either n + 1 or n - 1.
//
//
// Return the minimum number of operations needed for n to become 1.
//
// Example:
// Input: n = 8
// Output: 3
// Explanation: 8 -> 4 -> 2 -> 1
//
// Constraints:
// 1 <= n <= 231 - 1
//

/**
 * @param {number} n
 * @return {number}
 */
var integerReplacement = function(n) {
    let steps = 0;
    while (n !== 1) {
        if (n % 2 === 0) {
            n = n / 2;
        } else {
            if (n === 3 || ((n >> 1) & 1) === 0) {
                n = n - 1;
            } else {
                n = n + 1;
            }
        }
        steps++;
    }
    return steps;
};