// Source: https://leetcode.com/problems/combinations/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers n and k, return all possible combinations of k numbers chosen from the range [1, n].
//
// You may return the answer in any order.
//
// Example:
// Input: n = 4, k = 2
// Output: [[1,2],[1,3],[1,4],[2,3],[2,4],[3,4]]
// Explanation: There are 4 choose 2 = 6 total combinations.
// Note that combinations are unordered, i.e., [1,2] and [2,1] are considered to be the same combination.
//
// Constraints:
// 1 <= n <= 20
// 	1 <= k <= n
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** combine(int n, int k, int* returnSize, int** returnColumnSizes) {
    int totalCombinations = 1;
    for (int i = 0; i < k; i++) {
        totalCombinations = totalCombinations * (n - i) / (i + 1);
    }

    int** result = (int**)malloc(totalCombinations * sizeof(int*));
    *returnColumnSizes = (int*)malloc(totalCombinations * sizeof(int));
    *returnSize = 0;

    int* currentCombination = (int*)malloc(k * sizeof(int));

    void backtrack(int start, int depth) {
        if (depth == k) {
            result[*returnSize] = (int*)malloc(k * sizeof(int));
            memcpy(result[*returnSize], currentCombination, k * sizeof(int));
            (*returnColumnSizes)[*returnSize] = k;
            (*returnSize)++;
            return;
        }

        for (int i = start; i <= n - (k - depth); i++) {
            currentCombination[depth] = i;
            backtrack(i + 1, depth + 1);
        }
    }

    backtrack(1, 0);

    free(currentCombination);
    return result;      
}
