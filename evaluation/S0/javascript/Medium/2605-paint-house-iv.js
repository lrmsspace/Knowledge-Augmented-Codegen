// Source: https://leetcode.com/problems/paint-house-iv/   |   Difficulty: Medium
//
// Problem Description:
// You are given an even integer n representing the number of houses arranged in a straight line, and a 2D array cost of size n x 3, where cost[i][j] represents the cost of painting house i with color j + 1.
//
// The houses will look beautiful if they satisfy the following conditions:
//
//
// 	No two adjacent houses are painted the same color.
// 	Houses equidistant from the ends of the row are not painted the same color. For example, if n = 6, houses at positions (0, 5), (1, 4), and (2, 3) are considered equidistant.
//
//
// Return the minimum cost to paint the houses such that they look beautiful.
//
// Example:
// Input: n = 4, cost = [[3,5,7],[6,2,9],[4,8,1],[7,3,5]]
//
// Output: 9
//
// Explanation:
//
// The optimal painting sequence is [1, 2, 3, 2] with corresponding costs [3, 2, 1, 3]. This satisfies the following conditions:
//
//
// 	No adjacent houses have the same color.
// 	Houses at positions 0 and 3 (equidistant from the ends) are not painted the same color (1 != 2).
// 	Houses at positions 1 and 2 (equidistant from the ends) are not painted the same color (2 != 3).
//
//
// The minimum cost to paint the houses so that they look beautiful is 3 + 2 + 1 + 3 = 9.
//
// Constraints:
// 2 <= n <= 105
// 	n is even.
// 	cost.length == n
// 	cost[i].length == 3
// 	0 <= cost[i][j] <= 105
//

/**
 * @param {number} n
 * @param {number[][]} cost
 * @return {number}
 */
var minCost = function(n, cost) {
    const dp = Array.from({ length: n }, () => Array(3).fill(0));
    for (let j = 0; j < 3; j++) {
        dp[0][j] = cost[0][j];
    }
    for (let i = 1; i < n; i++) {
        for (let j = 0; j < 3; j++) {
            dp[i][j] = cost[i][j] + Math.min(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
        }
    }
    let minCost = Infinity;
    for (let j = 0; j < 3; j++) {
        minCost = Math.min(minCost, dp[n - 1][j]);
    }
    return minCost;
};