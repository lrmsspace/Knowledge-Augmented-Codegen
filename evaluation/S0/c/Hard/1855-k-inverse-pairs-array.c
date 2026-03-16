// Source: https://leetcode.com/problems/k-inverse-pairs-array/   |   Difficulty: Hard
//
// Problem Description:
// For an integer array nums, an inverse pair is a pair of integers [i, j] where 0 <= i < j < nums.length and nums[i] > nums[j].
//
// Given two integers n and k, return the number of different arrays consisting of numbers from 1 to n such that there are exactly k inverse pairs. Since the answer can be huge, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, k = 0
// Output: 1
// Explanation: Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pairs.
//
// Constraints:
// 1 <= n <= 1000
// 	0 <= k <= 1000
//

int kInversePairs(int n, int k) {
    if (k < 0 || k > n * (n - 1) / 2) return 0;
    const int MOD = 1000000007;
    int **dp = (int**)malloc((n + 1) * sizeof(int*));
    for (int i = 0; i <= n; ++i) {
        dp[i] = (int*)calloc((k + 1), sizeof(int));
    }
    dp[0][0] = 1;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[i][j] = dp[i - 1][j];
            if (j > 0) {
                dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
            }
            if (j >= i) {
                dp[i][j] = (dp[i][j] - dp[i - 1][j - i] + MOD) % MOD;
            }
        }
    }

    int result = dp[n][k];
    for (int i = 0; i <= n; ++i) {
        free(dp[i]);
    }
    free(dp);
    return result;      
}
