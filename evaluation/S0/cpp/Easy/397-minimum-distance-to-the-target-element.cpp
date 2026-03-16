// Source: https://leetcode.com/problems/minimum-distance-to-the-target-element/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums (0-indexed) and two integers target and start, find an index i such that nums[i] == target and abs(i - start) is minimized. Note that abs(x) is the absolute value of x.
//
// Return abs(i - start).
//
// It is guaranteed that target exists in nums.
//
// Example:
// Input: nums = [1,2,3,4,5], target = 5, start = 3
// Output: 1
// Explanation: nums[4] = 5 is the only value equal to target, so the answer is abs(4 - 3) = 1.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 104
// 	0 <= start < nums.length
// 	target is in nums.
//

class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start) {
        int minDistance = INT_MAX;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == target) {
                minDistance = min(minDistance, abs(i - start));
            }
        }
        return minDistance;         
    }
};
