// Source: https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of n integers, your task is to find the maximum value of k for which there exist two adjacent subarrays of length k each, such that both subarrays are strictly increasing. Specifically, check if there are two subarrays of length k starting at indices a and b (a < b), where:
//
//
// 	Both subarrays nums[a..a + k - 1] and nums[b..b + k - 1] are strictly increasing.
// 	The subarrays must be adjacent, meaning b = a + k.
//
//
// Return the maximum possible value of k.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [2,5,7,8,9,2,3,4,3,1]
//
// Output: 3
//
// Explanation:
//
//
// 	The subarray starting at index 2 is [7, 8, 9], which is strictly increasing.
// 	The subarray starting at index 5 is [2, 3, 4], which is also strictly increasing.
// 	These two subarrays are adjacent, and 3 is the maximum possible value of k for which two such adjacent strictly increasing subarrays exist.
//
// Constraints:
// 2 <= nums.length <= 2 * 105
// 	-109 <= nums[i] <= 109
//

int maxIncreasingSubarrays(int* nums, int numsSize) {
    int max_k = 0;
    int current_length = 1;
    int prev_length = 0;

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > nums[i - 1]) {
            current_length++;
        } else {
            prev_length = current_length;
            current_length = 1;
        }

        if (prev_length > 0) {
            max_k = (max_k > (prev_length < current_length ? prev_length : current_length)) ? max_k : (prev_length < current_length ? prev_length : current_length);
        }
    }

    return max_k;       
}
