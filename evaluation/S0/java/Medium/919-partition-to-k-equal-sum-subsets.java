// Source: https://leetcode.com/problems/partition-to-k-equal-sum-subsets/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return true if it is possible to divide this array into k non-empty subsets whose sums are all equal.
//
// Example:
// Input: nums = [4,3,2,3,5,2,1], k = 4
// Output: true
// Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3), (2,3) with equal sums.
//
// Constraints:
// 1 <= k <= nums.length <= 16
// 	1 <= nums[i] <= 104
// 	The frequency of each element is in the range [1, 4].
//

class Solution {
    public boolean canPartitionKSubsets(int[] nums, int k) {
        int totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }
        if (totalSum % k != 0) {
            return false;
        }
        int target = totalSum / k;
        boolean[] used = new boolean[nums.length];
        return backtrack(nums, used, k, 0, 0, target);          
    }
}
