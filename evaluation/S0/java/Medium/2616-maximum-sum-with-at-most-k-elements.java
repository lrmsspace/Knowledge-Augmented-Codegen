// Source: https://leetcode.com/problems/maximum-sum-with-at-most-k-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer matrix grid of size n x m, an integer array limits of length n, and an integer k. The task is to find the maximum sum of at most k elements from the matrix grid such that:
//
//
// 	
// 	The number of elements taken from the ith row of grid does not exceed limits[i].
// 	
//
//
// Return the maximum sum.
//
// Example:
// Input: grid = [[1,2],[3,4]], limits = [1,2], k = 2
//
// Output: 7
//
// Explanation:
//
//
// 	From the second row, we can take at most 2 elements. The elements taken are 4 and 3.
// 	The maximum possible sum of at most 2 selected elements is 4 + 3 = 7.
//
// Constraints:
// n == grid.length == limits.length
// 	m == grid[i].length
// 	1 <= n, m <= 500
// 	0 <= grid[i][j] <= 105
// 	0 <= limits[i] <= m
// 	0 <= k <= min(n * m, sum(limits))
//

class Solution {
    public long maxSum(int[][] grid, int[] limits, int k) {
        int n = grid.length;
        int m = grid[0].length;

        long[][] prefixSums = new long[n][m + 1];
        for (int i = 0; i < n; i++) {
            Arrays.sort(grid[i]);
            for (int j = 0; j < m; j++) {
                prefixSums[i][j + 1] = prefixSums[i][j] + grid[i][m - 1 - j];
            }
        }

        long[][] dp = new long[n + 1][k + 1];
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = dp[i - 1][j];
                for (int x = 1; x <= Math.min(limits[i - 1], j); x++) {
                    dp[i][j] = Math.max(dp[i][j], dp[i - 1][j - x] + prefixSums[i - 1][x]);
                }
            }
        }

        return dp[n][k];            
    }
}
