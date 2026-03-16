// Source: https://leetcode.com/problems/length-of-the-longest-subsequence-that-sums-to-target/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of integers nums, and an integer target.
//
// Return the length of the longest subsequence of nums that sums up to target. If no such subsequence exists, return -1.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [1,2,3,4,5], target = 9
// Output: 3
// Explanation: There are 3 subsequences with a sum equal to 9: [4,5], [1,3,5], and [2,3,4]. The longest subsequences are [1,3,5], and [2,3,4]. Hence, the answer is 3.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
// 	1 <= target <= 1000
//

class Solution {
public:
    int lengthOfLongestSubsequence(vector<int>& nums, int target) {
        vector<int> dp(target + 1, -1);
        dp[0] = 0; // Base case: sum of 0 can be achieved with length 0

        for (int num : nums) {
            for (int t = target; t >= num; --t) {
                if (dp[t - num] != -1) {
                    dp[t] = max(dp[t], dp[t - num] + 1);
                }
            }
        }

        return dp[target];          
    }
};
