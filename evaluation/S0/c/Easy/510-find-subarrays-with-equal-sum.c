// Source: https://leetcode.com/problems/find-subarrays-with-equal-sum/   |   Difficulty: Easy
//
// Problem Description:
// Given a 0-indexed integer array nums, determine whether there exist two subarrays of length 2 with equal sum. Note that the two subarrays must begin at different indices.
//
// Return true if these subarrays exist, and false otherwise.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [4,2,4]
// Output: true
// Explanation: The subarrays with elements [4,2] and [2,4] have the same sum of 6.
//
// Constraints:
// 2 <= nums.length <= 1000
// 	-109 <= nums[i] <= 109
//

bool findSubarrays(int* nums, int numsSize) {
    int seenSums[2001] = {0}; // To store sums of subarrays of length 2
    for (int i = 0; i < numsSize - 1; i++) {
        int sum = nums[i] + nums[i + 1];
        int index = sum + 1000; // Offset to handle negative sums
        if (seenSums[index]) {
            return true; // Found a duplicate sum
        }
        seenSums[index] = 1; // Mark this sum as seen
    }
    return false; // No duplicate sums found        
}
