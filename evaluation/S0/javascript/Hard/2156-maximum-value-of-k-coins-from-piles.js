// Source: https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/   |   Difficulty: Hard
//
// Problem Description:
// There are n piles of coins on a table. Each pile consists of a positive number of coins of assorted denominations.
//
// In one move, you can choose any coin on top of any pile, remove it, and add it to your wallet.
//
// Given a list piles, where piles[i] is a list of integers denoting the composition of the ith pile from top to bottom, and a positive integer k, return the maximum total value of coins you can have in your wallet if you choose exactly k coins optimally.
//
// Example:
// Input: piles = [[1,100,3],[7,8,9]], k = 2
// Output: 101
// Explanation:
// The above diagram shows the different ways we can choose k coins.
// The maximum total we can obtain is 101.
//
// Constraints:
// n == piles.length
// 	1 <= n <= 1000
// 	1 <= piles[i][j] <= 105
// 	1 <= k <= sum(piles[i].length) <= 2000
//

/**
 * @param {number[][]} piles
 * @param {number} k
 * @return {number}
 */
var maxValueOfCoins = function(piles, k) {
    const n = piles.length;
    const dp = new Array(k + 1).fill(0);
    for (let i = 0; i < n; i++) {
        const prefixSums = new Array(piles[i].length + 1).fill(0);
        for (let j = 0; j < piles[i].length; j++) {
            prefixSums[j + 1] = prefixSums[j] + piles[i][j];
        }
        for (let coins = k; coins >= 0; coins--) {
            for (let take = 0; take <= Math.min(coins, piles[i].length); take++) {
                dp[coins] = Math.max(dp[coins], dp[coins - take] + prefixSums[take]);
            }
        }
    }
    return dp[k];   
};
