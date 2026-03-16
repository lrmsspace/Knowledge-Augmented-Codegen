// Source: https://leetcode.com/problems/combination-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.
//
// The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.
//
// The test cases are generated such that the number of unique combinations that sum up to target is less than 150 combinations for the given input.
//
// Example:
// Input: candidates = [2,3,6,7], target = 7
// Output: [[2,2,3],[7]]
// Explanation:
// 2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
// 7 is a candidate, and 7 = 7.
// These are the only two combinations.
//
// Constraints:
// 1 <= candidates.length <= 30
// 	2 <= candidates[i] <= 40
// 	All elements of candidates are distinct.
// 	1 <= target <= 40
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
    int **res = NULL;
    int *path = (int *)malloc(sizeof(int) * target);
    int pathLen = 0;
    *returnSize = 0;
    *returnColumnSizes = NULL;

    void backtrack(int start, int sum) {
        if (sum == target) {
            res = (int **)realloc(res, sizeof(int *) * (*returnSize + 1));
            res[*returnSize] = (int *)malloc(sizeof(int) * pathLen);
            memcpy(res[*returnSize], path, sizeof(int) * pathLen);
            (*returnColumnSizes) = (int *)realloc(*returnColumnSizes, sizeof(int) * (*returnSize + 1));
            (*returnColumnSizes)[*returnSize] = pathLen;
            (*returnSize)++;
            return;
        }
        if (sum > target) {
            return;
        }
        for (int i = start; i < candidatesSize; i++) {
            path[pathLen++] = candidates[i];
            backtrack(i, sum + candidates[i]);
            pathLen--;
        }
    }

    backtrack(0, 0);
    free(path);
    return res;     
}
