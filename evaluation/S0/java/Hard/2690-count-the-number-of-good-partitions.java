// Source: https://leetcode.com/problems/count-the-number-of-good-partitions/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array nums consisting of positive integers.
//
// A partition of an array into one or more contiguous subarrays is called good if no two subarrays contain the same number.
//
// Return the total number of good partitions of nums.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [1,2,3,4]
// Output: 8
// Explanation: The 8 possible good partitions are: ([1], [2], [3], [4]), ([1], [2], [3,4]), ([1], [2,3], [4]), ([1], [2,3,4]), ([1,2], [3], [4]), ([1,2], [3,4]), ([1,2,3], [4]), and ([1,2,3,4]).
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//

class Solution {
    public int numberOfGoodPartitions(int[] nums) {
        int mod = 1_000_000_007;
        int n = nums.length;

        // dp[i] will store the number of good partitions for the first i elements
        long[] dp = new long[n + 1];
        dp[0] = 1; // Base case: one way to partition an empty array

        // lastSeen will store the last index where each number was seen
        Map<Integer, Integer> lastSeen = new HashMap<>();

        for (int i = 1; i <= n; i++) {
            int num = nums[i - 1];

            // If the number has been seen before, we need to subtract the partitions
            // that would create a duplicate subarray
            if (lastSeen.containsKey(num)) {
                int lastIndex = lastSeen.get(num);
                dp[i] = (dp[i - 1] - dp[lastIndex - 1] + mod) % mod;
            } else {
                dp[i] = dp[i - 1];
            }

            // Add the new partition ending at index i
            dp[i] = (dp[i] + dp[i - 1]) % mod;

            // Update the last seen index for the current number
            lastSeen.put(num, i);
        }

        return (int) dp[n];         
    }
}
