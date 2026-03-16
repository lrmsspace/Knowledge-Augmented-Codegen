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

int mergeStones(int* stones, int stonesSize, int k) {
    if ((stonesSize - 1) % (k - 1) != 0) return -1;

    int prefixSum[stonesSize + 1];
    prefixSum[0] = 0;
    for (int i = 0; i < stonesSize; ++i) {
        prefixSum[i + 1] = prefixSum[i] + stones[i];
    }

    int dp[stonesSize][stonesSize];
    memset(dp, 0, sizeof(dp));

    for (int length = k; length <= stonesSize; ++length) {
        for (int i = 0; i + length <= stonesSize; ++i) {
            int j = i + length - 1;
            dp[i][j] = __INT_MAX__;
            for (int mid = i; mid < j; mid += k - 1) {
                if (dp[i][mid] != __INT_MAX__ && dp[mid + 1][j] != __INT_MAX__) {
                    dp[i][j] = dp[i][j] < dp[i][mid] + dp[mid + 1][j]
                               ? dp[i][j]
                               : dp[i][mid] + dp[mid + 1][j];
                }
            }
            if ((length - 1) % (k - 1) == 0) {
                if (dp[i][j] != __INT_MAX__) {
                    dp[i][j] += prefixSum[j + 1] - prefixSum[i];
                }
            }
        }
    }

    return dp[0][stonesSize - 1];       
}
