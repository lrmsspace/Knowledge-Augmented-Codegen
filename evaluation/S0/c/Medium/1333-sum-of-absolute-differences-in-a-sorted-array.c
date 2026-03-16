// Source: https://leetcode.com/problems/sum-of-absolute-differences-in-a-sorted-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums sorted in non-decreasing order.
//
// Build and return an integer array result with the same length as nums such that result[i] is equal to the summation of absolute differences between nums[i] and all the other elements in the array.
//
// In other words, result[i] is equal to sum(|nums[i]-nums[j]|) where 0 <= j < nums.length and j != i (0-indexed).
//
// Example:
// Input: nums = [2,3,5]
// Output: [4,3,5]
// Explanation: Assuming the arrays are 0-indexed, then
// result[0] = |2-2| + |2-3| + |2-5| = 0 + 1 + 3 = 4,
// result[1] = |3-2| + |3-3| + |3-5| = 1 + 0 + 2 = 3,
// result[2] = |5-2| + |5-3| + |5-5| = 3 + 2 + 0 = 5.
//
// Constraints:
// 2 <= nums.length <= 105
// 	1 <= nums[i] <= nums[i + 1] <= 104
//



/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getSumAbsoluteDifferences(int* nums, int numsSize, int* returnSize){
    int* result = (int*)malloc(numsSize * sizeof(int));
    *returnSize = numsSize;

    int totalSum = 0;
    for (int i = 0; i < numsSize; i++) {
        totalSum += nums[i];
    }

    int leftSum = 0;
    for (int i = 0; i < numsSize; i++) {
        int rightSum = totalSum - leftSum - nums[i];
        result[i] = (nums[i] * i - leftSum) + (rightSum - nums[i] * (numsSize - i - 1));
        leftSum += nums[i];
    }

    return result;
}
