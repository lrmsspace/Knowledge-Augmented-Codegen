// Source: https://leetcode.com/problems/longest-increasing-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the length of the longest strictly increasing subsequence.
//
// Example:
// Input: nums = [10,9,2,5,3,7,101,18]
// Output: 4
// Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
//
// Constraints:
// 1 <= nums.length <= 2500
// 	-104 <= nums[i] <= 104
//
//
//  
// Follow up: Can you come up with an algorithm that runs in O(n log(n)) time complexity?
//

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp;
        for (int num : nums) {
            auto it = lower_bound(dp.begin(), dp.end(), num);
            if (it == dp.end()) {
                dp.push_back(num);
            } else {
                *it = num;
            }
        }
        return dp.size();           
    }
};
