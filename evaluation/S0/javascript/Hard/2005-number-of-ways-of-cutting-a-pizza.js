// Source: https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/   |   Difficulty: Hard
//
// Problem Description:
// Given a rectangular pizza represented as a rows x cols matrix containing the following characters: 'A' (an apple) and '.' (empty cell) and given the integer k. You have to cut the pizza into k pieces using k-1 cuts. 
//
// For each cut you choose the direction: vertical or horizontal, then you choose a cut position at the cell boundary and cut the pizza into two pieces. If you cut the pizza vertically, give the left part of the pizza to a person. If you cut the pizza horizontally, give the upper part of the pizza to a person. Give the last piece of pizza to the last person.
//
// Return the number of ways of cutting the pizza such that each piece contains at least one apple. Since the answer can be a huge number, return this modulo 10^9 + 7.
//
// Example:
// Input: pizza = ["A..","AAA","..."], k = 3
// Output: 3 
// Explanation: The figure above shows the three ways to cut the pizza. Note that pieces must contain at least one apple.
//
// Constraints:
// 1 <= rows, cols <= 50
// 	rows == pizza.length
// 	cols == pizza[i].length
// 	1 <= k <= 10
// 	pizza consists of characters 'A' and '.' only.
//

/**
 * @param {string[]} pizza
 * @param {number} k
 * @return {number}
 */
var ways = function(pizza, k) {
    const MOD = 1e9 + 7;
    const rows = pizza.length;
    const cols = pizza[0].length;
    const dp = Array.from({ length: rows + 1 }, () => new Array(cols + 1).fill(0)); 
    for (let i = rows - 1; i >= 0; i--) {
        for (let j = cols - 1; j >= 0; j--) {
            dp[i][j] = dp[i + 1][j] + dp[i][j + 1] - dp[i + 1][j + 1] + (pizza[i][j] === 'A' ? 1 : 0);
        }
    }
    const memo = Array.from({ length: rows }, () => new Array(cols).fill(0).map(() => new Array(k + 1).fill(-1)));
    const dfs = (i, j, cuts) => {
        if (cuts === 0) return dp[i][j] > 0 ? 1 : 0;
        if (memo[i][j][cuts] !== -1) return memo[i][j][cuts];
        let ways = 0;
        for (let x = i + 1; x < rows; x++) {
            if (dp[i][j] - dp[x][j] > 0) {
                ways = (ways + dfs(x, j, cuts - 1)) % MOD;
            }
        }
        for (let y = j + 1; y < cols; y++) {
            if (dp[i][j] - dp[i][y] > 0) {
                ways = (ways + dfs(i, y, cuts - 1)) % MOD;
            }
        }
        memo[i][j][cuts] = ways;
        return ways;
    }
    return dfs(0, 0, k - 1);
};
