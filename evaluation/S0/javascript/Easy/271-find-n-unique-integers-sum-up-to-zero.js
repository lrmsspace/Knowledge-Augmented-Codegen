// Source: https://leetcode.com/problems/find-n-unique-integers-sum-up-to-zero/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return any array containing n unique integers such that they add up to 0.
//
// Example:
// Input: n = 5
// Output: [-7,-1,1,3,4]
// Explanation: These arrays also are accepted [-5,-1,1,2,3] , [-3,-1,2,-2,4].
//
// Constraints:
// 1 <= n <= 1000
//

/**
 * @param {number} n
 * @return {number[]}
 */
var sumZero = function(n) {
    const result = [];
    for (let i = 1; i <= Math.floor(n / 2); i++) {
        result.push(i);
        result.push(-i);
    }
    if (n % 2 !== 0) {
        result.push(0);
    }
    return result;
};
