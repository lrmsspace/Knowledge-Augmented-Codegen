// Source: https://leetcode.com/problems/largest-number-at-least-twice-of-others/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums where the largest integer is unique.
//
// Determine whether the largest element in the array is at least twice as much as every other number in the array. If it is, return the index of the largest element, or return -1 otherwise.
//
// Example:
// Input: nums = [3,6,1,0]
// Output: 1
// Explanation: 6 is the largest integer.
// For every other number in the array x, 6 is at least twice as big as x.
// The index of value 6 is 1, so we return 1.
//
// Constraints:
// 2 <= nums.length <= 50
// 	0 <= nums[i] <= 100
// 	The largest element in nums is unique.
//

int dominantIndex(int* nums, int numsSize) {
    int maxIndex = 0;
    int maxValue = nums[0];

    // Find the index of the largest element
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > maxValue) {
            maxValue = nums[i];
            maxIndex = i;
        }
    }

    // Check if the largest element is at least twice as much as every other number
    for (int i = 0; i < numsSize; i++) {
        if (i != maxIndex && maxValue < 2 * nums[i]) {
            return -1;
        }
    }

    return maxIndex;
            
}
