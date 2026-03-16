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

long long sellingWood(int m, int n, int** prices, int pricesSize, int* pricesColSize) {
    long long dp[m + 1][n + 1];
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < pricesSize; ++i) {
        int h = prices[i][0], w = prices[i][1], price = prices[i][2];
        dp[h][w] = price;
    }

    for (int height = 1; height <= m; ++height) {
        for (int width = 1; width <= n; ++width) {
            for (int cutH = 1; cutH <= height / 2; ++cutH) {
                if (dp[cutH][width] + dp[height - cutH][width] > dp[height][width]) {
                    dp[height][width] = dp[cutH][width] + dp[height - cutH][width];
                }
            }
            for (int cutW = 1; cutW <= width / 2; ++cutW) {
                if (dp[height][cutW] + dp[height][width - cutW] > dp[height][width]) {
                    dp[height][width] = dp[height][cutW] + dp[height][width - cutW];
                }
            }
        }
    }

    return dp[m][n];        
}
