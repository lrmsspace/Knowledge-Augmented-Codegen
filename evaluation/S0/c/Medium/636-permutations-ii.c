// Source: https://leetcode.com/problems/permutations-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.
//
// Example:
// Input: nums = [1,1,2]
// Output:
// [[1,1,2],
//  [1,2,1],
//  [2,1,1]]
//
// Constraints:
// 1 <= nums.length <= 8
// 	-10 <= nums[i] <= 10
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    int maxPerms = 1;
    for (int i = 2; i <= numsSize; i++) {
        maxPerms *= i;
    }

    int** results = (int**)malloc(maxPerms * sizeof(int*));
    *returnColumnSizes = (int*)malloc(maxPerms * sizeof(int));
    *returnSize = 0;

    int* currentPerm = (int*)malloc(numsSize * sizeof(int));
    int* used = (int*)calloc(numsSize, sizeof(int));

    // Sort nums to handle duplicates
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    void backtrack(int depth) {
        if (depth == numsSize) {
            results[*returnSize] = (int*)malloc(numsSize * sizeof(int));
            memcpy(results[*returnSize], currentPerm, numsSize * sizeof(int));
            (*returnColumnSizes)[*returnSize] = numsSize;
            (*returnSize)++;
            return;
        }

        for (int i = 0; i < numsSize; i++) {
            if (used[i]) continue;
            if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;

            used[i] = 1;
            currentPerm[depth] = nums[i];
            backtrack(depth + 1);
            used[i] = 0;
        }
    }

    backtrack(0);

    free(currentPerm);
    free(used);

    return results;     
}
