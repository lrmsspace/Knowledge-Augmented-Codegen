// Source: https://leetcode.com/problems/knight-dialer/   |   Difficulty: Medium
//
// Problem Description:
// The chess knight has a unique movement, it may move two squares vertically and one square horizontally, or two squares horizontally and one square vertically (with both forming the shape of an L). The possible movements of chess knight are shown in this diagram:
//
// A chess knight can move as indicated in the chess diagram below:
//
// We have a chess knight and a phone pad as shown below, the knight can only stand on a numeric cell (i.e. blue cell).
//
// Given an integer n, return how many distinct phone numbers of length n we can dial.
//
// You are allowed to place the knight on any numeric cell initially and then you should perform n - 1 jumps to dial a number of length n. All jumps should be valid knight jumps.
//
// As the answer may be very large, return the answer modulo 109 + 7.
//
// Example:
// Input: n = 1
// Output: 10
// Explanation: We need to dial a number of length 1, so placing the knight over any numeric cell of the 10 cells is sufficient.
//
// Constraints:
// 1 <= n <= 5000
//

/**
 * @param {number} n
 * @return {number}
 */
var knightDialer = function(n) {
    const MOD = 1e9 + 7;
    const moves = {
        0: [4, 6],
        1: [6, 8],
        2: [7, 9],
        3: [4, 8],
        4: [0, 3, 9],
        5: [],
        6: [0, 1, 7],
        7: [2, 6],
        8: [1, 3],
        9: [2, 4]
    };
    let dp = Array(10).fill(1);
    for (let hop = 1; hop < n; hop++) {
        const newDp = Array(10).fill(0);
        for (let digit = 0; digit <= 9; digit++) {
            for (const next of moves[digit]) {
                newDp[next] = (newDp[next] + dp[digit]) % MOD;
            }
        }
        dp = newDp;
    }
    return dp.reduce((a, b) => (a + b) % MOD, 0);
};