// Source: https://leetcode.com/problems/find-target-indices-after-sorting-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums and a target element target.
//
// A target index is an index i such that nums[i] == target.
//
// Return a list of the target indices of nums after sorting nums in non-decreasing order. If there are no target indices, return an empty list. The returned list must be sorted in increasing order.
//
// Example:
// Input: nums = [1,2,5,2,3], target = 2
// Output: [1,2]
// Explanation: After sorting, nums is [1,2,2,3,5].
// The indices where nums[i] == 2 are 1 and 2.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i], target <= 100
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* targetIndices(int* nums, int numsSize, int target, int* returnSize) {
    // Counting sort approach
    int count[101] = {0}; // Since 1 <= nums[i], target <= 100
    for (int i = 0; i < numsSize; i++) {
        count[nums[i]]++;
    }

    int lessThanTarget = 0;
    for (int i = 1; i < target; i++) {
        lessThanTarget += count[i];
    }

    int targetCount = count[target];
    *returnSize = targetCount;
    int* result = (int*)malloc(targetCount * sizeof(int));
    for (int i = 0; i < targetCount; i++) {
        result[i] = lessThanTarget + i;
    }

    return result;      
}
