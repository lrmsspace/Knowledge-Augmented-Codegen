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
    public int numOfArrays(int n, int m, int k) {
        int MOD = 1_000_000_007;
        long[][][] dp = new long[n + 1][m + 1][k + 1];

        // Base case: For arrays of length 1
        for (int maxVal = 1; maxVal <= m; maxVal++) {
            dp[1][maxVal][1] = 1;
        }

        for (int len = 2; len <= n; len++) {
            for (int maxVal = 1; maxVal <= m; maxVal++) {
                for (int cost = 1; cost <= k; cost++) {
                    // Case 1: The last element is not a new maximum
                    dp[len][maxVal][cost] = (dp[len - 1][maxVal][cost] * maxVal) % MOD;

                    // Case 2: The last element is a new maximum
                    if (cost > 1) {
                        long sum = 0;
                        for (int prevMax = 1; prevMax < maxVal; prevMax++) {
                            sum = (sum + dp[len - 1][prevMax][cost - 1]) % MOD;
                        }
                        dp[len][maxVal][cost] = (dp[len][maxVal][cost] + sum) % MOD;
                    }
                }
            }
        }

        long result = 0;
        for (int maxVal = 1; maxVal <= m; maxVal++) {
            result = (result + dp[n][maxVal][k]) % MOD;
        }

        return (int) result;                    
    }
}
