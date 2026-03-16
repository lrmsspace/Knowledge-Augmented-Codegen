// Source: https://leetcode.com/problems/count-partitions-with-max-min-difference-at-most-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k. Your task is to partition nums into one or more non-empty contiguous segments such that in each segment, the difference between its maximum and minimum elements is at most k.
//
// Return the total number of ways to partition nums under this condition.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [9,4,1,3,7], k = 4
//
// Output: 6
//
// Explanation:
//
// There are 6 valid partitions where the difference between the maximum and minimum elements in each segment is at most k = 4:
//
//
// 	[[9], [4], [1], [3], [7]]
// 	[[9], [4], [1], [3, 7]]
// 	[[9], [4], [1, 3], [7]]
// 	[[9], [4, 1], [3], [7]]
// 	[[9], [4, 1], [3, 7]]
// 	[[9], [4, 1, 3], [7]]
//
// Constraints:
// 2 <= nums.length <= 5 * 104
// 	1 <= nums[i] <= 109
// 	0 <= k <= 109
//

int countPartitions(int* nums, int numsSize, int k) {
    const int MOD = 1e9 + 7;
    int dp[numsSize + 1];
    dp[0] = 1; // Base case: one way to partition an empty array

    for (int i = 1; i <= numsSize; i++) {
        int maxVal = nums[i - 1];
        int minVal = nums[i - 1];
        dp[i] = 0;

        // Check all possible partitions ending at index i-1
        for (int j = i - 1; j >= 0; j--) {
            maxVal = fmax(maxVal, nums[j]);
            minVal = fmin(minVal, nums[j]);

            if (maxVal - minVal <= k) {
                dp[i] = (dp[i] + dp[j]) % MOD;
            } else {
                break; // No need to check further as the difference will only increase
            }
        }
    }

    return dp[numsSize];        
}
