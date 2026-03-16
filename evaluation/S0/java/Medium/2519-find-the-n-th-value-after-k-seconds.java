// Source: https://leetcode.com/problems/find-the-n-th-value-after-k-seconds/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers n and k.
//
// Initially, you start with an array a of n integers where a[i] = 1 for all 0 <= i <= n - 1. After each second, you simultaneously update each element to be the sum of all its preceding elements plus the element itself. For example, after one second, a[0] remains the same, a[1] becomes a[0] + a[1], a[2] becomes a[0] + a[1] + a[2], and so on.
//
// Return the value of a[n - 1] after k seconds.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 4, k = 5
//
// Output: 56
//
// Explanation:
//
//
// 	
// 		
// 			Second
// 			State After
// 		
// 		
// 			0
// 			[1,1,1,1]
// 		
// 		
// 			1
// 			[1,2,3,4]
// 		
// 		
// 			2
// 			[1,3,6,10]
// 		
// 		
// 			3
// 			[1,4,10,20]
// 		
// 		
// 			4
// 			[1,5,15,35]
// 		
// 		
// 			5
// 			[1,6,21,56]
//
// Constraints:
// 1 <= n, k <= 1000
//

class Solution {
    public int valueAfterKSeconds(int n, int k) {
        int MOD = 1_000_000_007;
        int[][] dp = new int[k + 1][n + 1];

        // Base case: at time 0, all elements are 1
        for (int j = 0; j < n; j++) {
            dp[0][j] = 1;
        }

        // Fill the dp table
        for (int i = 1; i <= k; i++) {
            dp[i][0] = 1; // First element is always 1
            for (int j = 1; j < n; j++) {
                dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % MOD;
            }
        }

        return dp[k][n - 1];            
    }
}
