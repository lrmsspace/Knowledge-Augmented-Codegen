// Source: https://leetcode.com/problems/count-alternating-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary array nums.
//
// We call a subarray alternating if no two adjacent elements in the subarray have the same value.
//
// Return the number of alternating subarrays in nums.
//
// Example:
// Input: nums = [0,1,1,1]
//
// Output: 5
//
// Explanation:
//
// The following subarrays are alternating: [0], [1], [1], [1], and [0,1].
//
// Constraints:
// 1 <= nums.length <= 105
// 	nums[i] is either 0 or 1.
//

long long countAlternatingSubarrays(int* nums, int numsSize) {
    long long count = 0;
    int length = 1;  // Length of the current alternating subarray

    for (int i = 0; i < numsSize; i++) {
        count++;  // Each single element is an alternating subarray
    }

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] != nums[i - 1]) {
            length++;
        } else {
            length = 1;  // Reset length if the current element is the same as the previous one
        }
        count += length - 1;  // Add the number of new alternating subarrays ending at index i
    }

    return count;       
}
