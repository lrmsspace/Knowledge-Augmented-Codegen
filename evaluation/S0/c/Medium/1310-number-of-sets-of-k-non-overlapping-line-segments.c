// Source: https://leetcode.com/problems/number-of-sets-of-k-non-overlapping-line-segments/   |   Difficulty: Medium
//
// Problem Description:
// Given n points on a 1-D plane, where the ith point (from 0 to n-1) is at x = i, find the number of ways we can draw exactly k non-overlapping line segments such that each segment covers two or more points. The endpoints of each segment must have integral coordinates. The k line segments do not have to cover all n points, and they are allowed to share endpoints.
//
// Return the number of ways we can draw k non-overlapping line segments. Since this number can be huge, return it modulo 109 + 7.
//
// Example:
// Input: n = 4, k = 2
// Output: 5
// Explanation: The two line segments are shown in red and blue.
// The image above shows the 5 different ways {(0,2),(2,3)}, {(0,1),(1,3)}, {(0,1),(2,3)}, {(1,2),(2,3)}, {(0,1),(1,2)}.
//
// Constraints:
// 2 <= n <= 1000
// 	1 <= k <= n-1
//

int numberOfSets(int n, int k) {
    const int MOD = 1e9 + 7;
    long long dp[n + 1][k + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = 0;
        }
    }
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= k; j++) {
            dp[i][j] = (dp[i - 1][j] + dp[i - 1][j - 1] * (i - 1)) % MOD;
        }
    }
    return (int)dp[n][k];       
}
