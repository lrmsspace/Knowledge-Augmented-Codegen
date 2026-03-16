// Source: https://leetcode.com/problems/find-all-duplicates-in-an-array/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums of length n where all the integers of nums are in the range [1, n] and each integer appears at most twice, return an array of all the integers that appears twice.
//
// You must write an algorithm that runs in O(n) time and uses only constant auxiliary space, excluding the space needed to store the output
//
// Example:
// Input: nums = [4,3,2,7,8,2,3,1]
// Output: [2,3]
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	1 <= nums[i] <= n
// 	Each element in nums appears once or twice.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDuplicates(int* nums, int numsSize, int* returnSize) {
    int* result = (int*)malloc(numsSize * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < numsSize; i++) {
        int index = abs(nums[i]) - 1; // Get the index corresponding to the value

        if (nums[index] < 0) {
            // If the value at this index is negative, it means we've seen this number before
            result[(*returnSize)++] = abs(nums[i]);
        } else {
            // Mark the number as seen by negating the value at the corresponding index
            nums[index] = -nums[index];
        }
    }

    return result;      
}
