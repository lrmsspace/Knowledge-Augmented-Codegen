// Source: https://leetcode.com/problems/maximum-width-ramp/   |   Difficulty: Medium
//
// Problem Description:
// A ramp in an integer array nums is a pair (i, j) for which i < j and nums[i] <= nums[j]. The width of such a ramp is j - i.
//
// Given an integer array nums, return the maximum width of a ramp in nums. If there is no ramp in nums, return 0.
//
// Example:
// Input: nums = [6,0,8,2,1,5]
// Output: 4
// Explanation: The maximum width ramp is achieved at (i, j) = (1, 5): nums[1] = 0 and nums[5] = 5.
//
// Constraints:
// 2 <= nums.length <= 5 * 104
// 	0 <= nums[i] <= 5 * 104
//

class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();
        vector<int> stack;
        
        // Build a decreasing stack of indices
        for (int i = 0; i < n; ++i) {
            if (stack.empty() || nums[i] < nums[stack.back()]) {
                stack.push_back(i);
            }
        }

        int maxWidth = 0;
        
        // Traverse from the end to find maximum width ramp
        for (int j = n - 1; j >= 0; --j) {
            while (!stack.empty() && nums[j] >= nums[stack.back()]) {
                maxWidth = max(maxWidth, j - stack.back());
                stack.pop_back();
            }
        }

        return maxWidth;            
    }
};
