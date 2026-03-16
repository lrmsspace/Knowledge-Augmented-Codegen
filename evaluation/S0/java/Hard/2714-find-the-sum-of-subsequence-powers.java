// Source: https://leetcode.com/problems/find-the-sum-of-subsequence-powers/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of length n, and a positive integer k.
//
// The power of a subsequence is defined as the minimum absolute difference between any two elements in the subsequence.
//
// Return the sum of powers of all subsequences of nums which have length equal to k.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4], k = 3
//
// Output: 4
//
// Explanation:
//
// There are 4 subsequences in nums which have length 3: [1,2,3], [1,3,4], [1,2,4], and [2,3,4]. The sum of powers is |2 - 3| + |3 - 4| + |2 - 1| + |3 - 4| = 4.
//
// Constraints:
// 2 <= n == nums.length <= 50
// 	-108 <= nums[i] <= 108 
// 	2 <= k <= n
//

class Solution {
    public int sumOfPowers(int[] nums, int k) {
        int MOD = 1_000_000_007;
        int n = nums.length;
        Arrays.sort(nums);
        
        long result = 0;
        
        for (int diff = 0; diff <= 200_000_000; diff++) {
            long[][] dp = new long[n + 1][k + 1];
            dp[0][0] = 1;
            
            for (int i = 1; i <= n; i++) {
                for (int j = 0; j <= k; j++) {
                    dp[i][j] = dp[i - 1][j];
                    
                    if (j > 0) {
                        int prevIndex = findPrevIndex(nums, i - 1, diff);
                        dp[i][j] = (dp[i][j] + dp[prevIndex + 1][j - 1]) % MOD;
                    }
                }
            }
            
            result = (result + dp[n][k] * diff) % MOD;
        }
        
        return (int) result;            
    }
}
