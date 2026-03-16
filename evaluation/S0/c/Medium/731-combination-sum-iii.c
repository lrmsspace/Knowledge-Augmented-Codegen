// Source: https://leetcode.com/problems/combination-sum-iii/   |   Difficulty: Medium
//
// Problem Description:
// Find all valid combinations of k numbers that sum up to n such that the following conditions are true:
//
//
// 	Only numbers 1 through 9 are used.
// 	Each number is used at most once.
//
//
// Return a list of all possible valid combinations. The list must not contain the same combination twice, and the combinations may be returned in any order.
//
// Example:
// Input: k = 3, n = 7
// Output: [[1,2,4]]
// Explanation:
// 1 + 2 + 4 = 7
// There are no other valid combinations.
//
// Constraints:
// 2 <= k <= 9
// 	1 <= n <= 60
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combinationSum3(int k, int n, int* returnSize, int** returnColumnSizes) {
    int** result = (int**)malloc(10000 * sizeof(int*));
    *returnColumnSizes = (int*)malloc(10000 * sizeof(int));
    *returnSize = 0;

    int path[9];
    int pathSize = 0;

    void backtrack(int start, int k, int n) {
        if (n == 0 && pathSize == k) {
            result[*returnSize] = (int*)malloc(pathSize * sizeof(int));
            memcpy(result[*returnSize], path, pathSize * sizeof(int));
            (*returnColumnSizes)[*returnSize] = pathSize;
            (*returnSize)++;
            return;
        }
        if (n < 0 || pathSize > k) {
            return;
        }
        for (int i = start; i <= 9; i++) {
            path[pathSize++] = i;
            backtrack(i + 1, k, n - i);
            pathSize--;
        }
    }

    backtrack(1, k, n);
    return result;      
}
