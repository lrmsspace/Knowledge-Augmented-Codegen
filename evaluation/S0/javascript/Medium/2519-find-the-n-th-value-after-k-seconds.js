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

/**
 * @param {number} n
 * @param {number} k
 * @return {number}
 */
var valueAfterKSeconds = function(n, k) {
    const mod = 1e9 + 7;
    const dp = Array.from({ length: k + 1 }, () => Array(n).fill(0));
    for (let i = 0; i < n; i++) {
        dp[0][i] = 1;
    }
    for (let t = 1; t <= k; t++) {
        for (let i = 0; i < n; i++) {
            dp[t][i] = (dp[t][i - 1] + dp[t - 1][i]) % mod;
        }
    }
    return dp[k][n - 1];    
};
