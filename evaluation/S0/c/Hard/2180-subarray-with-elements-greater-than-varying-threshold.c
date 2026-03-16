// Source: https://leetcode.com/problems/subarray-with-elements-greater-than-varying-threshold/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer threshold.
//
// Find any subarray of nums of length k such that every element in the subarray is greater than threshold / k.
//
// Return the size of any such subarray. If there is no such subarray, return -1.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,3,4,3,1], threshold = 6
// Output: 3
// Explanation: The subarray [3,4,3] has a size of 3, and every element is greater than 6 / 3 = 2.
// Note that this is the only valid subarray.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i], threshold <= 109
//

int validSubarraySize(int* nums, int numsSize, int threshold) {
    if (!nums || numsSize <= 0) return -1;

    int count = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] * count > threshold) {
            return count;
        }
        if (nums[i] * (count + 1) > threshold) {
            ++count;
        } else {
            count = 0;
        }
    }
    return -1;      
}
