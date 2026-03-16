// Source: https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of size n.
//
// Consider a non-empty subarray from nums that has the maximum possible bitwise AND.
//
//
// 	In other words, let k be the maximum value of the bitwise AND of any subarray of nums. Then, only subarrays with a bitwise AND equal to k should be considered.
//
//
// Return the length of the longest such subarray.
//
// The bitwise AND of an array is the bitwise AND of all the numbers in it.
//
// A subarray is a contiguous sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,3,3,2,2]
// Output: 2
// Explanation:
// The maximum possible bitwise AND of a subarray is 3.
// The longest subarray with that value is [3,3], so we return 2.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//

int longestSubarray(int* nums, int numsSize) {
    int max_val = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > max_val) {
            max_val = nums[i];
        }
    }

    int longest = 0;
    int current_length = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == max_val) {
            current_length++;
            if (current_length > longest) {
                longest = current_length;
            }
        } else {
            current_length = 0;
        }
    }

    return longest;     
}
