// Source: https://leetcode.com/problems/minimum-addition-to-make-integer-beautiful/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers n and target.
//
// An integer is considered beautiful if the sum of its digits is less than or equal to target.
//
// Return the minimum non-negative integer x such that n + x is beautiful. The input will be generated such that it is always possible to make n beautiful.
//
// Example:
// Input: n = 16, target = 6
// Output: 4
// Explanation: Initially n is 16 and its digit sum is 1 + 6 = 7. After adding 4, n becomes 20 and digit sum becomes 2 + 0 = 2. It can be shown that we can not make n beautiful with adding non-negative integer less than 4.
//
// Constraints:
// 1 <= n <= 1012
// 	1 <= target <= 150
// 	The input will be generated such that it is always possible to make n beautiful.
//

/**
 * @param {number} n
 * @param {number} target
 * @return {number}
 */
var makeIntegerBeautiful = function(n, target) {
    const digitSum = (num) => {
        let sum = 0;
        while (num > 0) {
            sum += num % 10;
            num = Math.floor(num / 10);
        }
        return sum;
    };

    if (digitSum(n) <= target) {
        return 0;
    }

    let addition = 0;
    let multiplier = 1;

    while (digitSum(n + addition) > target) {
        const remainder = (n + addition) % 10;
        addition += (10 - remainder) * multiplier;
        multiplier *= 10;
    }

    return addition;
};