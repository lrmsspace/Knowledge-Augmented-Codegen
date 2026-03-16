// Source: https://leetcode.com/problems/minimum-absolute-difference-between-elements-with-constraint/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and an integer x.
//
// Find the minimum absolute difference between two elements in the array that are at least x indices apart.
//
// In other words, find two indices i and j such that abs(i - j) >= x and abs(nums[i] - nums[j]) is minimized.
//
// Return an integer denoting the minimum absolute difference between two elements that are at least x indices apart.
//
// Example:
// Input: nums = [4,3,2,4], x = 2
// Output: 0
// Explanation: We can select nums[0] = 4 and nums[3] = 4. 
// They are at least 2 indices apart, and their absolute difference is the minimum, 0. 
// It can be shown that 0 is the optimal answer.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	0 <= x < nums.length
//

class Solution {
public:
    int minAbsoluteDifference(vector<int>& nums, int x) {
        set<int> bst;
        int minDiff = INT_MAX;

        for (int i = x; i < nums.size(); ++i) {
            bst.insert(nums[i - x]);

            auto it = bst.lower_bound(nums[i]);
            if (it != bst.end()) {
                minDiff = min(minDiff, abs(nums[i] - *it));
            }
            if (it != bst.begin()) {
                --it;
                minDiff = min(minDiff, abs(nums[i] - *it));
            }
        }

        return minDiff;         
    }
};
