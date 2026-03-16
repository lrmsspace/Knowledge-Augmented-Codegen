// Source: https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums, where nums[i] represents the score of the ith student. You are also given an integer k.
//
// Pick the scores of any k students from the array so that the difference between the highest and the lowest of the k scores is minimized.
//
// Return the minimum possible difference.
//
// Example:
// Input: nums = [90], k = 1
// Output: 0
// Explanation: There is one way to pick score(s) of one student:
// - [90]. The difference between the highest and lowest score is 90 - 90 = 0.
// The minimum possible difference is 0.
//
// Constraints:
// 1 <= k <= nums.length <= 1000
// 	0 <= nums[i] <= 105
//

class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) {
        if (k == 1) return 0;

        sort(nums.begin(), nums.end());
        int minDiff = INT_MAX;

        for (int i = 0; i <= nums.size() - k; ++i) {
            int diff = nums[i + k - 1] - nums[i];
            minDiff = min(minDiff, diff);
        }

        return minDiff;         
    }
};
