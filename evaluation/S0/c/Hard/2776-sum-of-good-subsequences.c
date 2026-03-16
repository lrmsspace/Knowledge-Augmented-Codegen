// Source: https://leetcode.com/problems/sum-of-good-subsequences/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums. A good subsequence is defined as a subsequence of nums where the absolute difference between any two consecutive elements in the subsequence is exactly 1.
//
// Return the sum of all possible good subsequences of nums.
//
// Since the answer may be very large, return it modulo 109 + 7.
//
// Note that a subsequence of size 1 is considered good by definition.
//
// Example:
// Input: nums = [1,2,1]
//
// Output: 14
//
// Explanation:
//
//
// 	Good subsequences are: [1], [2], [1], [1,2], [2,1], [1,2,1].
// 	The sum of elements in these subsequences is 14.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
//

int sumOfGoodSubsequences(int* nums, int numsSize) {
    if (!nums || numsSize <= 0) return 0;

    const int MOD = 1000000007;
    const int MAX_VAL = 100000;

    long long *dp = (long long*)calloc(MAX_VAL + 1, sizeof(long long));
    if (!dp) return 0;

    for (int i = 0; i < numsSize; ++i) {
        int val = nums[i];
        long long prev1 = (val > 0) ? dp[val - 1] : 0;
        long long prev2 = (val < MAX_VAL) ? dp[val + 1] : 0;
        long long newCount = (1 + prev1 + prev2) % MOD; // subsequence of size 1 + extending from val-1 and val+1
        dp[val] = (dp[val] + newCount) % MOD;
    }

    long long result = 0;
    for (int i = 0; i <= MAX_VAL; ++i) {
        result = (result + dp[i]) % MOD;
    }

    free(dp);
    return (int)result;     
}
