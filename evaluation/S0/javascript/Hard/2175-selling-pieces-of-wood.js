// Source: https://leetcode.com/problems/selling-pieces-of-wood/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers m and n that represent the height and width of a rectangular piece of wood. You are also given a 2D integer array prices, where prices[i] = [hi, wi, pricei] indicates you can sell a rectangular piece of wood of height hi and width wi for pricei dollars.
//
// To cut a piece of wood, you must make a vertical or horizontal cut across the entire height or width of the piece to split it into two smaller pieces. After cutting a piece of wood into some number of smaller pieces, you can sell pieces according to prices. You may sell multiple pieces of the same shape, and you do not have to sell all the shapes. The grain of the wood makes a difference, so you cannot rotate a piece to swap its height and width.
//
// Return the maximum money you can earn after cutting an m x n piece of wood.
//
// Note that you can cut the piece of wood as many times as you want.
//
// Example:
// Input: m = 3, n = 5, prices = [[1,4,2],[2,2,7],[2,1,3]]
// Output: 19
// Explanation: The diagram above shows a possible scenario. It consists of:
// - 2 pieces of wood shaped 2 x 2, selling for a price of 2 * 7 = 14.
// - 1 piece of wood shaped 2 x 1, selling for a price of 1 * 3 = 3.
// - 1 piece of wood shaped 1 x 4, selling for a price of 1 * 2 = 2.
// This obtains a total of 14 + 3 + 2 = 19 money earned.
// It can be shown that 19 is the maximum amount of money that can be earned.
//
// Constraints:
// 1 <= m, n <= 200
// 	1 <= prices.length <= 2 * 104
// 	prices[i].length == 3
// 	1 <= hi <= m
// 	1 <= wi <= n
// 	1 <= pricei <= 106
// 	All the shapes of wood (hi, wi) are pairwise distinct.
//

/**
 * @param {number} m
 * @param {number} n
 * @param {number[][]} prices
 * @return {number}
 */
var sellingWood = function(m, n, prices) {
    const dp = Array.from({ length: m + 1 }, () => new Array(n + 1).fill(0));
    for (const [hi, wi, price] of prices) {
        dp[hi][wi] = price;
    }
    for (let height = 1; height <= m; height++) {
        for (let width = 1; width <= n; width++) {
            for (let cutHeight = 1; cutHeight < height; cutHeight++) {
                dp[height][width] = Math.max(dp[height][width], dp[cutHeight][width] + dp[height - cutHeight][width]);
            }
            for (let cutWidth = 1; cutWidth < width; cutWidth++) {
                dp[height][width] = Math.max(dp[height][width], dp[height][cutWidth] + dp[height][width - cutWidth]);
            }
        }
    }
    return dp[m][n];
};
