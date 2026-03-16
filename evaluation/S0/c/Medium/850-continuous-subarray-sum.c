// Source: https://leetcode.com/problems/continuous-subarray-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and an integer k, return true if nums has a good subarray or false otherwise.
//
// A good subarray is a subarray where:
//
//
// 	its length is at least two, and
// 	the sum of the elements of the subarray is a multiple of k.
//
//
// Note that:
//
//
// 	A subarray is a contiguous part of the array.
// 	An integer x is a multiple of k if there exists an integer n such that x = n * k. 0 is always a multiple of k.
//
// Example:
// Input: nums = [23,2,4,6,7], k = 6
// Output: true
// Explanation: [2, 4] is a continuous subarray of size 2 whose elements sum up to 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
// 	0 <= sum(nums[i]) <= 231 - 1
// 	1 <= k <= 231 - 1
//

bool checkSubarraySum(int* nums, int numsSize, int k) {
    int modIndex[k];
    for (int i = 0; i < k; i++) {
        modIndex[i] = -2; // Initialize all indices to -2
    }
    modIndex[0] = -1; // To handle the case where the subarray starts from index 0

    int cumulativeSum = 0;
    for (int i = 0; i < numsSize; i++) {
        cumulativeSum += nums[i];
        int mod = cumulativeSum % k;

        if (modIndex[mod] != -2) {
            if (i - modIndex[mod] > 1) {
                return true; // Found a valid subarray
            }
        } else {
            modIndex[mod] = i; // Store the first occurrence of this mod value
        }
    }

    return false; // No valid subarray found        
}
