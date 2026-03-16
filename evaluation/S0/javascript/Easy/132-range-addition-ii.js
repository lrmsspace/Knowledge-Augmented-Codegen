// Source: https://leetcode.com/problems/range-addition-ii/   |   Difficulty: Easy
//
// Problem Description:
// You are given an m x n matrix M initialized with all 0's and an array of operations ops, where ops[i] = [ai, bi] means M[x][y] should be incremented by one for all 0 <= x < ai and 0 <= y < bi.
//
// Count and return the number of maximum integers in the matrix after performing all the operations.
//
// Example:
// Input: m = 3, n = 3, ops = [[2,2],[3,3]]
// Output: 4
// Explanation: The maximum integer in M is 2, and there are four of it in M. So return 4.
//
// Constraints:
// 1 <= m, n <= 4 * 104
// 	0 <= ops.length <= 104
// 	ops[i].length == 2
// 	1 <= ai <= m
// 	1 <= bi <= n
//

/**
 * @param {number} m
 * @param {number} n
 * @param {number[][]} ops
 * @return {number}
 */
var maxCount = function(m, n, ops) {
    if (ops.length === 0) {
        return m * n;
    }
    let minA = m;
    let minB = n;
    for (let i = 0; i < ops.length; i++) {
        if (ops[i][0] < minA) {
            minA = ops[i][0];
        }
        if (ops[i][1] < minB) {
            minB = ops[i][1];
        }
    }
    return minA * minB;         
};
