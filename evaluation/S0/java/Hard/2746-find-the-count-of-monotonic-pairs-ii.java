// Source: https://leetcode.com/problems/find-the-count-of-monotonic-pairs-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums of length n.
//
// We call a pair of non-negative integer arrays (arr1, arr2) monotonic if:
//
//
// 	The lengths of both arrays are n.
// 	arr1 is monotonically non-decreasing, in other words, arr1[0] <= arr1[1] <= ... <= arr1[n - 1].
// 	arr2 is monotonically non-increasing, in other words, arr2[0] >= arr2[1] >= ... >= arr2[n - 1].
// 	arr1[i] + arr2[i] == nums[i] for all 0 <= i <= n - 1.
//
//
// Return the count of monotonic pairs.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,3,2]
//
// Output: 4
//
// Explanation:
//
// The good pairs are:
//
//
// 	([0, 1, 1], [2, 2, 1])
// 	([0, 1, 2], [2, 2, 0])
// 	([0, 2, 2], [2, 1, 0])
// 	([1, 2, 2], [1, 1, 0])
//
// Constraints:
// 1 <= n == nums.length <= 2000
// 	1 <= nums[i] <= 1000
//

class Solution {
    public int countOfPairs(int[] nums) {
        int mod = (int)1e9 + 7;
        int n = nums.length;
        long[][] dp = new long[n + 1][1001];
        
        // Base case: There's one way to form an empty array
        for (int j = 0; j <= 1000; j++) {
            dp[0][j] = 1;
        }
        
        for (int i = 1; i <= n; i++) {
            long prefixSum = 0;
            for (int j = 0; j <= 1000; j++) {
                prefixSum = (prefixSum + dp[i - 1][j]) % mod;
                if (j <= nums[i - 1]) {
                    dp[i][j] = prefixSum;
                } else {
                    dp[i][j] = dp[i][j - 1];
                }
            }
        }
        
        return (int)dp[n][1000];            
    }
}
