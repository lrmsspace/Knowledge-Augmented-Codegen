// Source: https://leetcode.com/problems/largest-positive-integer-that-exists-with-its-negative/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums that does not contain any zeros, find the largest positive integer k such that -k also exists in the array.
//
// Return the positive integer k. If there is no such integer, return -1.
//
// Example:
// Input: nums = [-1,2,-3,3]
// Output: 3
// Explanation: 3 is the only valid k we can find in the array.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-1000 <= nums[i] <= 1000
// 	nums[i] != 0
//

int findMaxK(int* nums, int numsSize) {
    int seen[2001] = {0}; // Array to track seen numbers from -1000 to 1000
    int maxK = -1;

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        seen[num + 1000] = 1; // Shift index by 1000 to handle negative indices
    }

    for (int k = 1000; k >= 1; k--) {
        if (seen[k + 1000] && seen[-k + 1000]) {
            return k; // Return the largest k found
        }
    }

    return -1; // No valid k found      
}
