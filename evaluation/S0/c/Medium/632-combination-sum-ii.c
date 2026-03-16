// Source: https://leetcode.com/problems/combination-sum-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.
//
// Each number in candidates may only be used once in the combination.
//
// Note: The solution set must not contain duplicate combinations.
//
// Example:
// Input: candidates = [10,1,2,7,6,1,5], target = 8
// Output: 
// [
// [1,1,6],
// [1,2,5],
// [1,7],
// [2,6]
// ]
//
// Constraints:
// 1 <= candidates.length <= 100
// 	1 <= candidates[i] <= 50
// 	1 <= target <= 30
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    int** result = NULL;
    *returnSize = 0;
    *returnColumnSizes = NULL;
    int* combination = (int*)malloc(sizeof(int) * target);
    int combinationSize = 0;

    // Sort candidates to handle duplicates
    qsort(candidates, candidatesSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    void backtrack(int start, int remaining) {
        if (remaining == 0) {
            result = (int**)realloc(result, sizeof(int*) * (*returnSize + 1));
            result[*returnSize] = (int*)malloc(sizeof(int) * combinationSize);
            memcpy(result[*returnSize], combination, sizeof(int) * combinationSize);
            (*returnColumnSizes) = (int*)realloc(*returnColumnSizes, sizeof(int) * (*returnSize + 1));
            (*returnColumnSizes)[*returnSize] = combinationSize;
            (*returnSize)++;
            return;
        }
        for (int i = start; i < candidatesSize; i++) {
            if (i > start && candidates[i] == candidates[i - 1]) continue; // Skip duplicates
            if (candidates[i] > remaining) break; // No need to continue if the candidate exceeds the remaining target
            combination[combinationSize++] = candidates[i];
            backtrack(i + 1, remaining - candidates[i]); // Move to the next index
            combinationSize--;
        }
    }

    backtrack(0, target);
    free(combination);
    return result;      
}
