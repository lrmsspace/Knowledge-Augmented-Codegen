// Source: https://leetcode.com/problems/subsets-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums that may contain duplicates, return all possible subsets (the power set).
//
// The solution set must not contain duplicate subsets. Return the solution in any order.
//
// Example:
// Input: nums = [1,2,2]
// Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]
//
// Constraints:
// 1 <= nums.length <= 10
// 	-10 <= nums[i] <= 10
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsetsWithDup(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int totalSubsets = 1 << numsSize; // 2^n possible subsets
    int** result = (int**)malloc(totalSubsets * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalSubsets * sizeof(int));
    *returnSize = 0;

    // Sort the input array to handle duplicates
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    for (int i = 0; i < totalSubsets; i++) {
        int* subset = (int*)malloc(numsSize * sizeof(int));
        int subsetSize = 0;
        int isValid = 1;

        for (int j = 0; j < numsSize; j++) {
            if (i & (1 << j)) {
                // Check for duplicates
                if (j > 0 && nums[j] == nums[j - 1] && !(i & (1 << (j - 1)))) {
                    isValid = 0;
                    break;
                }
                subset[subsetSize++] = nums[j];
            }
        }

        if (isValid) {
            result[*returnSize] = (int*)malloc(subsetSize * sizeof(int));
            memcpy(result[*returnSize], subset, subsetSize * sizeof(int));
            (*returnColumnSizes)[*returnSize] = subsetSize;
            (*returnSize)++;
        }
        free(subset);
    }

    return result;      
}
