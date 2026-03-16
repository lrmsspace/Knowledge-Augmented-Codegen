// Source: https://leetcode.com/problems/consecutive-numbers-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer n, return the number of ways you can write n as the sum of consecutive positive integers.
//
// Example:
// Input: n = 5
// Output: 2
// Explanation: 5 = 2 + 3
//
// Constraints:
// 1 <= n <= 109
//

/**
 * @param {number} n
 * @return {number}
 */
var consecutiveNumbersSum = function(n) {
    // The sum of k consecutive numbers starting from m is given by the formula: S = m + (m + 1) + ... + (m + k - 1) = k * m + (k * (k - 1)) / 2. We can rearrange this to find m: m = (S - (k * (k - 1)) / 2) / k. For m to be a positive integer, the expression (S - (k * (k - 1)) / 2) must be positive and divisible by k. This means that S must be greater than (k * (k - 1)) / 2 and S - (k * (k - 1)) / 2 must be divisible by k. We can iterate over possible values of k and check these conditions to count the number of valid sequences.
    let count = 0;
    for (let k = 1; k * (k - 1) / 2 < n; k++) {
        if ((n - (k * (k - 1) / 2)) % k === 0) {
            count++;
        }
    }
    return count;
};
