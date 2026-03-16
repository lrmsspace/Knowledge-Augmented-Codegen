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

int getMinDistance(int* nums, int numsSize, int target, int start) {
    int min_distance = numsSize; // Initialize with a large value

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == target) {
            int distance = abs(i - start);
            if (distance < min_distance) {
                min_distance = distance;
            }
        }
    }

    return min_distance;        
}
