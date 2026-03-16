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

class Solution {
    public int countPartitions(int[] nums, int k) {
        int mod = 1_000_000_007;
        int n = nums.length;
        long totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        if (totalSum < 2L * k) {
            return 0;
        }

        long maxInvalidSum = k - 1;
        long[] dp = new long[(int) maxInvalidSum + 1];
        dp[0] = 1;

        for (int num : nums) {
            for (int sum = (int) maxInvalidSum; sum >= num; sum--) {
                dp[sum] = (dp[sum] + dp[sum - num]) % mod;
            }
        }

        long invalidPartitions = 0;
        for (long count : dp) {
            invalidPartitions = (invalidPartitions + count) % mod;
        }

        long totalPartitions = modPow(2, n, mod);
        long greatPartitions = (totalPartitions - (2 * invalidPartitions) % mod + mod) % mod;

        return (int) greatPartitions;           
    }
}
