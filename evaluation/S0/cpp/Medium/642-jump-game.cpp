// Source: https://leetcode.com/problems/jump-game/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.
//
// Return true if you can reach the last index, or false otherwise.
//
// Example:
// Input: nums = [2,3,1,1,4]
// Output: true
// Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
//
// Constraints:
// 1 <= nums.length <= 104
// 	0 <= nums[i] <= 105
//

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int farthest = 0;
        for (int i = 0; i < n; ++i) {
            if (i > farthest) {
                return false;
            }
            farthest = max(farthest, i + nums[i]);
            if (farthest >= n - 1) {
                return true;
            }
        }
        return false;           
    }
};
