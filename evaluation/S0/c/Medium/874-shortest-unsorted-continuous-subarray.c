// Source: https://leetcode.com/problems/shortest-unsorted-continuous-subarray/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, you need to find one continuous subarray such that if you only sort this subarray in non-decreasing order, then the whole array will be sorted in non-decreasing order.
//
// Return the shortest such subarray and output its length.
//
// Example:
// Input: nums = [2,6,4,8,10,9,15]
// Output: 5
// Explanation: You need to sort [6, 4, 8, 10, 9] in ascending order to make the whole array sorted in ascending order.
//
// Constraints:
// 1 <= nums.length <= 104
// 	-105 <= nums[i] <= 105
//
//
//  
// Follow up: Can you solve it in O(n) time complexity?
//

int findUnsortedSubarray(int* nums, int numsSize) {
    int left = 0, right = numsSize - 1;
    int max = nums[0], min = nums[numsSize - 1];

    // Find the right boundary of the unsorted subarray
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] >= max) {
            max = nums[i];
        } else {
            right = i;
        }
    }

    // Find the left boundary of the unsorted subarray
    for (int i = numsSize - 1; i >= 0; i--) {
        if (nums[i] <= min) {
            min = nums[i];
        } else {
            left = i;
        }
    }

    return right > left ? right - left + 1 : 0;     
}
