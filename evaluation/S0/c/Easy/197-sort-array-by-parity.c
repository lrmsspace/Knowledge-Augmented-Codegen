// Source: https://leetcode.com/problems/sort-array-by-parity/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, move all the even integers at the beginning of the array followed by all the odd integers.
//
// Return any array that satisfies this condition.
//
// Example:
// Input: nums = [3,1,2,4]
// Output: [2,4,3,1]
// Explanation: The outputs [4,2,3,1], [2,4,1,3], and [4,2,1,3] would also be accepted.
//
// Constraints:
// 1 <= nums.length <= 5000
// 	0 <= nums[i] <= 5000
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sortArrayByParity(int* nums, int numsSize, int* returnSize) {
    int* result = (int*)malloc(numsSize * sizeof(int));
    int evenIndex = 0;
    int oddIndex = numsSize - 1;

    for (int i = 0; i < numsSize; i++) {
        if (nums[i] % 2 == 0) {
            result[evenIndex++] = nums[i];
        } else {
            result[oddIndex--] = nums[i];
        }
    }

    *returnSize = numsSize;
    return result;      
}
