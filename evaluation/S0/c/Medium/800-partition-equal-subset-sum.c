// Source: https://leetcode.com/problems/partition-equal-subset-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.
//
// Example:
// Input: nums = [1,5,11,5]
// Output: true
// Explanation: The array can be partitioned as [1, 5, 5] and [11].
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 100
//

bool canPartition(int* nums, int numsSize) {
    int totalSum = 0;
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];
    }
    if (totalSum % 2 != 0) {
        return false;
    }
    int target = totalSum / 2;
    bool dp[target + 1];
    for (int i = 0; i <= target; i++) {
        dp[i] = false;
    }
    dp[0] = true;

    for (int i = 0; i < numsSize; i++) {
        for (int j = target; j >= nums[i]; j--) {
            dp[j] = dp[j] || dp[j - nums[i]];
        }
    }
    return dp[target];      
}
