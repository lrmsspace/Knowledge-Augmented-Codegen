// Source: https://leetcode.com/problems/diagonal-traverse-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D integer array nums, return all elements of nums in diagonal order as shown in the below images.
//
// Example:
// Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,4,2,7,5,3,8,6,9]
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i].length <= 105
// 	1 <= sum(nums[i].length) <= 105
// 	1 <= nums[i][j] <= 105
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDiagonalOrder(int** nums, int numsSize, int* numsColSize, int* returnSize) {
    int totalElements = 0;
    for (int i = 0; i < numsSize; i++) {
        totalElements += numsColSize[i];
    }

    int* result = (int*)malloc(totalElements * sizeof(int));
    int index = 0;

    for (int d = 0; d < numsSize + 100000; d++) {
        for (int i = 0; i <= d; i++) {
            int j = d - i;
            if (i < numsSize && j < numsColSize[i]) {
                result[index++] = nums[i][j];
            }
        }
    }

    *returnSize = totalElements;
    return result;      
}
