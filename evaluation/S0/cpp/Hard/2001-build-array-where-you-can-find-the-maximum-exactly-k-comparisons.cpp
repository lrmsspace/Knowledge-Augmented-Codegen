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

class Solution {
public:
    int numOfArrays(int n, int m, int k) {
        const int MOD = 1e9 + 7;
        // dp[i][j][p]: number of arrays of length i, max value j, search cost p
        vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(m + 1, vector<long long>(k + 1, 0)));
        
        // Base case: arrays of length 1
        for (int j = 1; j <= m; j++) {
            dp[1][j][1] = 1;
        }
        
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int p = 1; p <= k; p++) {
                    // Case 1: last element is not a new maximum
                    dp[i][j][p] = (dp[i][j][p] + dp[i - 1][j][p] * j) % MOD;
                    
                    // Case 2: last element is a new maximum
                    for (int x = 1; x < j; x++) {
                        dp[i][j][p] = (dp[i][j][p] + dp[i - 1][x][p - 1]) % MOD;
                    }
                }
            }
        }
        
        long long result = 0;
        for (int j = 1; j <= m; j++) {
            result = (result + dp[n][j][k]) % MOD;
        }
        
        return (int)result;         
    }
};
