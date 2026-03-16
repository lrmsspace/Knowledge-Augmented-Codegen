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
    public boolean canJump(int[] nums) {
        int maxReachable = 0;
        for (int i = 0; i < nums.length; i++) {
            if (i > maxReachable) {
                return false;
            }
            maxReachable = Math.max(maxReachable, i + nums[i]);
        }
        return true;            
    }
}
