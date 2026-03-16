// Source: https://leetcode.com/problems/minimum-cost-to-merge-stones/   |   Difficulty: Hard
//
// Problem Description:
// There are n piles of stones arranged in a row. The ith pile has stones[i] stones.
//
// A move consists of merging exactly k consecutive piles into one pile, and the cost of this move is equal to the total number of stones in these k piles.
//
// Return the minimum cost to merge all piles of stones into one pile. If it is impossible, return -1.
//
// Example:
// Input: stones = [3,2,4,1], k = 2
// Output: 20
// Explanation: We start with [3, 2, 4, 1].
// We merge [3, 2] for a cost of 5, and we are left with [5, 4, 1].
// We merge [4, 1] for a cost of 5, and we are left with [5, 5].
// We merge [5, 5] for a cost of 10, and we are left with [10].
// The total cost was 20, and this is the minimum possible.
//
// Constraints:
// n == stones.length
// 	1 <= n <= 30
// 	1 <= stones[i] <= 100
// 	2 <= k <= 30
//

class Solution {
    public int mergeStones(int[] stones, int k) {
        int n = stones.length;
        if ((n - 1) % (k - 1) != 0) {
            return -1;
        }

        int[][] dp = new int[n][n];
        int[] prefixSum = new int[n + 1];
        for (int i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + stones[i];
        }

        for (int length = k; length <= n; length++) {
            for (int i = 0; i <= n - length; i++) {
                int j = i + length - 1;
                dp[i][j] = Integer.MAX_VALUE;
                for (int mid = i; mid < j; mid += k - 1) {
                    dp[i][j] = Math.min(dp[i][j], dp[i][mid] + dp[mid + 1][j]);
                }
                if ((length - 1) % (k - 1) == 0) {
                    dp[i][j] += prefixSum[j + 1] - prefixSum[i];
                }
            }
        }

        return dp[0][n - 1];                    
    }
}
