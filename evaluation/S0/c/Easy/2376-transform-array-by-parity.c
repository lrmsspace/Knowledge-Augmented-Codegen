// Source: https://leetcode.com/problems/transform-array-by-parity/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums. Transform nums by performing the following operations in the exact order specified:
//
//
// 	Replace each even number with 0.
// 	Replace each odd numbers with 1.
// 	Sort the modified array in non-decreasing order.
//
//
// Return the resulting array after performing these operations.
//
// Example:
// Input: nums = [4,3,2,1]
//
// Output: [0,0,1,1]
//
// Explanation:
//
//
// 	Replace the even numbers (4 and 2) with 0 and the odd numbers (3 and 1) with 1. Now, nums = [0, 1, 0, 1].
// 	After sorting nums in non-descending order, nums = [0, 0, 1, 1].
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 1000
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* transformArray(int* nums, int numsSize, int* returnSize) {
    int* result = (int*)malloc(numsSize * sizeof(int));
    int zeroCount = 0;
    int oneCount = 0;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % 2 == 0) {
            result[i] = 0;
            zeroCount++;
        } else {
            result[i] = 1;
            oneCount++;
        }
    }

    // Fill the result array with sorted values
    for (int i = 0; i < zeroCount; i++) {
        result[i] = 0;
    }
    for (int i = zeroCount; i < numsSize; i++) {
        result[i] = 1;
    }

    *returnSize = numsSize;
    return result;      
}
