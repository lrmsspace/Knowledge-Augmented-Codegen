// Source: https://leetcode.com/problems/number-of-subarrays-with-bounded-maximum/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and two integers left and right, return the number of contiguous non-empty subarrays such that the value of the maximum array element in that subarray is in the range [left, right].
//
// The test cases are generated so that the answer will fit in a 32-bit integer.
//
// Example:
// Input: nums = [2,1,4,3], left = 2, right = 3
// Output: 3
// Explanation: There are three subarrays that meet the requirements: [2], [2, 1], [3].
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
// 	0 <= left <= right <= 109
//

int numSubarrayBoundedMax(int* nums, int numsSize, int left, int right) {
    int count = 0;
    int start = -1;  // Start index of the current valid segment
    int lastValid = -1;  // Last index where nums[i] is within [left, right]

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > right) {
            start = i;  // Reset start index if nums[i] exceeds right
        } else if (nums[i] >= left) {
            lastValid = i;  // Update last valid index
        }
        // Count valid subarrays ending at index i
        count += lastValid - start;
    }

    return count;       
}
