// Source: https://leetcode.com/problems/permutations/   |   Difficulty: Medium
//
// Problem Description:
// Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
//
// Example:
// Input: nums = [1,2,3]
// Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
//
// Constraints:
// 1 <= nums.length <= 6
// 	-10 <= nums[i] <= 10
// 	All the integers of nums are unique.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int total_permutations = 1;
    for (int i = 2; i <= numsSize; i++) {
        total_permutations *= i;
    }

    int** result = (int**)malloc(total_permutations * sizeof(int*));
    *returnColumnSizes = (int*)malloc(total_permutations * sizeof(int));
    *returnSize = 0;

    void backtrack(int* current_permutation, int current_size, int* used) {
        if (current_size == numsSize) {
            result[*returnSize] = (int*)malloc(numsSize * sizeof(int));
            memcpy(result[*returnSize], current_permutation, numsSize * sizeof(int));
            (*returnColumnSizes)[*returnSize] = numsSize;
            (*returnSize)++;
            return;
        }

        for (int i = 0; i < numsSize; i++) {
            if (used[i]) continue;

            used[i] = 1;
            current_permutation[current_size] = nums[i];
            backtrack(current_permutation, current_size + 1, used);
            used[i] = 0;
        }
    }

    int* current_permutation = (int*)malloc(numsSize * sizeof(int));
    int* used = (int*)calloc(numsSize, sizeof(int));

    backtrack(current_permutation, 0, used);

    free(current_permutation);
    free(used);

    return result;      
}
