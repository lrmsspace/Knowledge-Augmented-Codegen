// Source: https://leetcode.com/problems/maximum-sum-of-two-non-overlapping-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and two integers firstLen and secondLen, return the maximum sum of elements in two non-overlapping subarrays with lengths firstLen and secondLen.
//
// The array with length firstLen could occur before or after the array with length secondLen, but they have to be non-overlapping.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [0,6,5,2,2,5,1,9,4], firstLen = 1, secondLen = 2
// Output: 20
// Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.
//
// Constraints:
// 1 <= firstLen, secondLen <= 1000
// 	2 <= firstLen + secondLen <= 1000
// 	firstLen + secondLen <= nums.length <= 1000
// 	0 <= nums[i] <= 1000
//

int maxSumTwoNoOverlap(int* nums, int numsSize, int firstLen, int secondLen) {
    int maxSum = 0;

    // Helper function to calculate maximum sum of two non-overlapping subarrays
    int maxSumHelper(int* nums, int numsSize, int len1, int len2) {
        int maxSum1 = 0, maxSum2 = 0;
        int sum1 = 0, sum2 = 0;

        // Calculate prefix sums for the first subarray
        for (int i = 0; i < len1; i++) {
            sum1 += nums[i];
        }
        maxSum1 = sum1;

        for (int i = len1; i < numsSize; i++) {
            sum1 += nums[i] - nums[i - len1];
            maxSum1 = fmax(maxSum1, sum1);

            if (i >= len1 + len2 - 1) {
                sum2 += nums[i - len1] - nums[i - len1 - len2];
                maxSum2 = fmax(maxSum2, sum2);
            }
        }

        return maxSum1 + maxSum2;
    }

    // Calculate maximum sum for both arrangements
    maxSum = fmax(maxSumHelper(nums, numsSize, firstLen, secondLen),
                  maxSumHelper(nums, numsSize, secondLen, firstLen));

    return maxSum;      
}
