// Source: https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums of size n where n is a multiple of 3 and a positive integer k.
//
// Divide the array nums into n / 3 arrays of size 3 satisfying the following condition:
//
//
// 	The difference between any two elements in one array is less than or equal to k.
//
//
// Return a 2D array containing the arrays. If it is impossible to satisfy the conditions, return an empty array. And if there are multiple answers, return any of them.
//
// Example:
// Input: nums = [1,3,4,8,7,9,3,5,1], k = 2
//
// Output: [[1,1,3],[3,4,5],[7,8,9]]
//
// Explanation:
//
// The difference between any two elements in each array is less than or equal to 2.
//
// Constraints:
// n == nums.length
// 	1 <= n <= 105
// 	n is a multiple of 3
// 	1 <= nums[i] <= 105
// 	1 <= k <= 105
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** divideArray(int* nums, int numsSize, int k, int* returnSize, int** returnColumnSizes) {
    // Sort the input array to facilitate grouping
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int groupCount = numsSize / 3;
    int** result = (int**)malloc(groupCount * sizeof(int*));
    *returnColumnSizes = (int*)malloc(groupCount * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < groupCount; i++) {
        int idx = i * 3;
        // Check if the max difference condition is satisfied
        if (nums[idx + 2] - nums[idx] > k) {
            // Free allocated memory before returning empty result
            for (int j = 0; j < *returnSize; j++) {
                free(result[j]);
            }
            free(result);
            free(*returnColumnSizes);
            *returnSize = 0;
            return NULL;
        }
        // Allocate memory for the current group and fill it
        result[i] = (int*)malloc(3 * sizeof(int));
        result[i][0] = nums[idx];
        result[i][1] = nums[idx + 1];
        result[i][2] = nums[idx + 2];
        (*returnColumnSizes)[i] = 3;
        (*returnSize)++;
    }

    return result;      
}
