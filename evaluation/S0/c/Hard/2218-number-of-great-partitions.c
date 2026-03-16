// Source: https://leetcode.com/problems/number-of-great-partitions/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array nums consisting of positive integers and an integer k.
//
// Partition the array into two ordered groups such that each element is in exactly one group. A partition is called great if the sum of elements of each group is greater than or equal to k.
//
// Return the number of distinct great partitions. Since the answer may be too large, return it modulo 109 + 7.
//
// Two partitions are considered distinct if some element nums[i] is in different groups in the two partitions.
//
// Example:
// Input: nums = [1,2,3,4], k = 4
// Output: 6
// Explanation: The great partitions are: ([1,2,3], [4]), ([1,3], [2,4]), ([1,4], [2,3]), ([2,3], [1,4]), ([2,4], [1,3]) and ([4], [1,2,3]).
//
// Constraints:
// 1 <= nums.length, k <= 1000
// 	1 <= nums[i] <= 109
//

int countPartitions(int* nums, int numsSize, int k) {
    const int MOD = 1000000007;
    int total = 0;
    for (int i = 0; i < numsSize; i++) {
        total += nums[i];
    }
    if (total < 2 * k) return 0;

    int dp[k];
    memset(dp, 0, sizeof(dp));
    dp[0] = 1;
    for (int i = 0; i < numsSize; i++) {
        int val = nums[i];
        for (int j = k - 1; j >= val; j--) {
            dp[j] = (dp[j] + dp[j - val]) % MOD;
        }
    }

    int invalid = 0;
    for (int j = 0; j < k; j++) {
        invalid = (invalid + dp[j]) % MOD;
    }

    long long totalWays = 1;
    for (int i = 0; i < numsSize; i++) {
        totalWays = (totalWays * 2) % MOD;
    }

    long long result = (totalWays - (2LL * invalid) % MOD + MOD) % MOD;
    return (int)result;     
}
