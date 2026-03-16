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

class Solution {
    public int maxValueOfCoins(List<List<Integer>> piles, int k) {
        int n = piles.size();
        int[][] dp = new int[n + 1][k + 1];

        for (int i = 1; i <= n; i++) {
            List<Integer> pile = piles.get(i - 1);
            int m = pile.size();
            int[] prefixSum = new int[m + 1];
            for (int j = 1; j <= m; j++) {
                prefixSum[j] = prefixSum[j - 1] + pile.get(j - 1);
            }

            for (int j = 0; j <= k; j++) {
                dp[i][j] = dp[i - 1][j]; // Not taking any coins from the current pile
                for (int x = 1; x <= Math.min(j, m); x++) {
                    dp[i][j] = Math.max(dp[i][j], dp[i - 1][j - x] + prefixSum[x]);
                }
            }
        }

        return dp[n][k];            
    }
}
