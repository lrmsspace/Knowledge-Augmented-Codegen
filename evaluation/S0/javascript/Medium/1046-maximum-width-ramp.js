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

/**
 * @param {number[]} nums
 * @return {number}
 */
var maxWidthRamp = function(nums) {
    const n = nums.length;
    const stack = [];
    for (let i = 0; i < n; i++) {
        if (stack.length === 0 || nums[i] < nums[stack[stack.length - 1]]) {
            stack.push(i);
        }
    }
    let maxWidth = 0;
    for (let j = n - 1; j >= 0; j--) {
        while (stack.length > 0 && nums[j] >= nums[stack[stack.length - 1]]) {
            const i = stack.pop();
            maxWidth = Math.max(maxWidth, j - i);
        }
    }
    return maxWidth;
        
};
