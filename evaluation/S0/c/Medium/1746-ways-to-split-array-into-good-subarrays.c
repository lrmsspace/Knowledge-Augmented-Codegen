// Source: https://leetcode.com/problems/ways-to-split-array-into-good-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary array nums.
//
// A subarray of an array is good if it contains exactly one element with the value 1.
//
// Return an integer denoting the number of ways to split the array nums into good subarrays. As the number may be too large, return it modulo 109 + 7.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [0,1,0,0,1]
// Output: 3
// Explanation: There are 3 ways to split nums into good subarrays:
// - [0,1] [0,0,1]
// - [0,1,0] [0,1]
// - [0,1,0,0] [1]
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 1
//

int numberOfGoodSubarraySplits(int* nums, int numsSize) {
    const int MOD = 1e9 + 7;
    long long result = 1;
    int i = 0;

    // Skip leading zeros
    while (i < numsSize && nums[i] == 0) {
        i++;
    }

    // If there are no 1s in the array, return 0
    if (i == numsSize) {
        return 0;
    }

    // Iterate through the array to find gaps between 1s
    for (; i < numsSize; ) {
        // Move to the next 1
        while (i < numsSize && nums[i] == 1) {
            i++;
        }

        // Count zeros between two 1s
        int zeroCount = 0;
        while (i < numsSize && nums[i] == 0) {
            zeroCount++;
            i++;
        }

        // If we found a gap of zeros between two 1s, update the result
        if (i < numsSize) {
            result = (result * (zeroCount + 1)) % MOD;
        }
    }

    return (int)result;     
}
