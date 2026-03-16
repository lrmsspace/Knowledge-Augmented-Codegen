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

int maxValueOfCoins(int** piles, int pilesSize, int* pilesColSize, int k) {
    int *dp = (int*)calloc(k + 1, sizeof(int));
    if (!dp) return 0;
    for (int i = 0; i < pilesSize; i++) {
        int pileSize = pilesColSize[i];
        int *prefixSums = (int*)calloc(pileSize + 1, sizeof(int));
        if (!prefixSums) {
            free(dp);
            return 0;
        }
        for (int j = 0; j < pileSize; j++) {
            prefixSums[j + 1] = prefixSums[j] + piles[i][j];
        }
        for (int j = k; j >= 0; j--) {
            for (int x = 1; x <= pileSize && x <= j; x++) {
                if (dp[j - x] + prefixSums[x] > dp[j]) {
                    dp[j] = dp[j - x] + prefixSums[x];
                }
            }
        }
        free(prefixSums);
    }
    int result = dp[k];
    free(dp);
    return result;      
}
