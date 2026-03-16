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

int maxWidthRamp(int* nums, int numsSize) {
    int maxWidth = 0;
    int stack[numsSize];
    int stackSize = 0;

    // Build a decreasing stack of indices
    for (int i = 0; i < numsSize; i++) {
        if (stackSize == 0 || nums[i] < nums[stack[stackSize - 1]]) {
            stack[stackSize++] = i;
        }
    }

    // Traverse from the end to find maximum width ramp
    for (int j = numsSize - 1; j >= 0; j--) {
        while (stackSize > 0 && nums[j] >= nums[stack[stackSize - 1]]) {
            int i = stack[--stackSize];
            maxWidth = (j - i) > maxWidth ? (j - i) : maxWidth;
        }
    }

    return maxWidth;        
}
