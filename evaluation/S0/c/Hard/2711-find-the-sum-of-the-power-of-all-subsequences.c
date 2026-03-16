// Source: https://leetcode.com/problems/find-the-sum-of-the-power-of-all-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of length n and a positive integer k.
//
// The power of an array of integers is defined as the number of subsequences with their sum equal to k.
//
// Return the sum of power of all subsequences of nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input:   nums = [1,2,3], k = 3 
//
// Output:   6 
//
// Explanation:
//
// There are 5 subsequences of nums with non-zero power:
//
//
// 	The subsequence [1,2,3] has 2 subsequences with sum == 3: [1,2,3] and [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
// 	The subsequence [1,2,3] has 1 subsequence with sum == 3: [1,2,3].
//
//
// Hence the answer is 2 + 1 + 1 + 1 + 1 = 6.
//
// Constraints:
// 1 <= n <= 100
// 	1 <= nums[i] <= 104
// 	1 <= k <= 100
//

int sumOfPower(int* nums, int numsSize, int k) {
    if (!nums || numsSize <= 0) return 0;
    const int MOD = 1000000007;

    int dp[k + 1];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1; /* empty subsequence */

    for (int i = 0; i < numsSize; ++i) {
        int num = nums[i];
        for (int s = k; s >= num; --s) {
            dp[s] = (dp[s] + dp[s - num]) % MOD;
        }
    }

    return dp[k];       
}
