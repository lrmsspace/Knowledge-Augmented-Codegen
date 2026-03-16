// Source: https://leetcode.com/problems/remove-one-element-to-make-the-array-strictly-increasing/   |   Difficulty: Easy
//
// Problem Description:
// Given a 0-indexed integer array nums, return true if it can be made strictly increasing after removing exactly one element, or false otherwise. If the array is already strictly increasing, return true.
//
// The array nums is strictly increasing if nums[i - 1] < nums[i] for each index (1 <= i < nums.length).
//
// Example:
// Input: nums = [1,2,10,5,7]
// Output: true
// Explanation: By removing 10 at index 2 from nums, it becomes [1,2,5,7].
// [1,2,5,7] is strictly increasing, so return true.
//
// Constraints:
// 2 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
//

class Solution {
public:
    bool canBeIncreasing(vector<int>& nums) {
        int count = 0;
        int n = nums.size();
        for (int i = 1; i < n && count <= 1; ++i) {
            if (nums[i] <= nums[i - 1]) {
                ++count;
                if (i == 1 || nums[i] > nums[i - 2]) {
                    // Remove nums[i - 1]
                    continue;
                } else {
                    // Remove nums[i]
                    nums[i] = nums[i - 1];
                }
            }
        }
        return count <= 1;          
    }
};
