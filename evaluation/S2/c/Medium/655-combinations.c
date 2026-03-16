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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

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

    int* combination = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        combination[i] = i + 1;
    }

    while (1) {
        result[*returnSize] = (int*)malloc(k * sizeof(int));
        memcpy(result[*returnSize], combination, k * sizeof(int));
        (*returnColumnSizes)[*returnSize] = k;
        (*returnSize)++;

        int idx = k - 1;
        while (idx >= 0 && combination[idx] == n - k + idx + 1) {
            idx--;
        }
        if (idx < 0) {
            break;
        }
        combination[idx]++;
        for (int j = idx + 1; j < k; j++) {
            combination[j] = combination[j - 1] + 1;
        }
    }

    free(combination);
    return result;      
}
