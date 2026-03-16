// Source: https://leetcode.com/problems/non-decreasing-subsequences/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements. You may return the answer in any order.
//
// Example:
// Input: nums = [4,6,7,7]
// Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
//
// Constraints:
// 1 <= nums.length <= 15
// 	-100 <= nums[i] <= 100
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** findSubsequences(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int** result = NULL;
    *returnSize = 0;
    *returnColumnSizes = NULL;

    int path[numsSize];
    int pathSize = 0;

    void backtrack(int startIndex) {
        if (pathSize >= 2) {
            result = realloc(result, sizeof(int*) * (*returnSize + 1));
            (*returnColumnSizes) = realloc(*returnColumnSizes, sizeof(int) * (*returnSize + 1));
            result[*returnSize] = malloc(sizeof(int) * pathSize);
            memcpy(result[*returnSize], path, sizeof(int) * pathSize);
            (*returnColumnSizes)[*returnSize] = pathSize;
            (*returnSize)++;
        }

        int used[201] = {0}; // To track used numbers at this depth

        for (int i = startIndex; i < numsSize; i++) {
            if ((pathSize == 0 || nums[i] >= path[pathSize - 1]) && !used[nums[i] + 100]) {
                used[nums[i] + 100] = 1; // Mark this number as used
                path[pathSize++] = nums[i];
                backtrack(i + 1);
                pathSize--;
            }
        }
    }

    backtrack(0);
    return result;      
}
