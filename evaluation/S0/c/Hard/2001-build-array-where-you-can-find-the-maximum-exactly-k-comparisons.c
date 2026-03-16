// Source: https://leetcode.com/problems/build-array-where-you-can-find-the-maximum-exactly-k-comparisons/   |   Difficulty: Hard
//
// Problem Description:
// You are given three integers n, m and k. Consider the following algorithm to find the maximum element of an array of positive integers:
//
// You should build the array arr which has the following properties:
//
//
// 	arr has exactly n integers.
// 	1 <= arr[i] <= m where (0 <= i < n).
// 	After applying the mentioned algorithm to arr, the value search_cost is equal to k.
//
//
// Return the number of ways to build the array arr under the mentioned conditions. As the answer may grow large, the answer must be computed modulo 109 + 7.
//
// Example:
// Input: n = 2, m = 3, k = 1
// Output: 6
// Explanation: The possible arrays are [1, 1], [2, 1], [2, 2], [3, 1], [3, 2] [3, 3]
//
// Constraints:
// 1 <= n <= 50
// 	1 <= m <= 100
// 	0 <= k <= n
//

int numOfArrays(int n, int m, int k) {
    const int MOD = 1000000007;
    int dp[51][101][51];
    memset(dp, 0, sizeof(dp));
    for (int maxVal = 1; maxVal <= m; ++maxVal) {
        dp[1][maxVal][1] = 1;
    }
    for (int len = 2; len <= n; ++len) {
        for (int maxVal = 1; maxVal <= m; ++maxVal) {
            for (int cost = 1; cost <= k; ++cost) {
                /* case 1: append an element <= maxVal */
                dp[len][maxVal][cost] = (int)((dp[len][maxVal][cost] +
                    (long long)dp[len - 1][maxVal][cost] * maxVal) % MOD);
                /* case 2: append an element > maxVal */
                for (int newMax = maxVal + 1; newMax <= m; ++newMax) {
                    dp[len][newMax][cost + 1] = (int)((dp[len][newMax][cost + 1] +
                        (long long)dp[len - 1][maxVal][cost]) % MOD);
                }
            }
        }
    }
    int result = 0;
    for (int maxVal = 1; maxVal <= m; ++maxVal) {
        result = (result + dp[n][maxVal][k]) % MOD;
    }
    return result;      
}
