// Source: https://leetcode.com/problems/maximum-difference-between-adjacent-elements-in-a-circular-array/   |   Difficulty: Easy
//
// Problem Description:
// Given a circular array nums, find the maximum absolute difference between adjacent elements.
//
// Note: In a circular array, the first and last elements are adjacent.
//
// Example:
// Input: nums = [1,2,4]
//
// Output: 3
//
// Explanation:
//
// Because nums is circular, nums[0] and nums[2] are adjacent. They have the maximum absolute difference of |4 - 1| = 3.
//
// Constraints:
// 2 <= nums.length <= 100
// 	-100 <= nums[i] <= 100
//

int maxAdjacentDistance(int* nums, int numsSize) {
    int max_diff = 0;
    for (int i = 0; i < numsSize; i++) {
        int next_index = (i + 1) % numsSize;
        int diff = abs(nums[i] - nums[next_index]);
        if (diff > max_diff) {
            max_diff = diff;
        }
    }
    return max_diff;        
}
