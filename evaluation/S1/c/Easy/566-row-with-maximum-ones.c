// Source: https://leetcode.com/problems/row-with-maximum-ones/   |   Difficulty: Easy
//
// Problem Description:
// Given a m x n binary matrix mat, find the 0-indexed position of the row that contains the maximum count of ones, and the number of ones in that row.
//
// In case there are multiple rows that have the maximum count of ones, the row with the smallest row number should be selected.
//
// Return an array containing the index of the row, and the number of ones in it.
//
// Example:
// Input: mat = [[0,1],[1,0]]
// Output: [0,1]
// Explanation: Both rows have the same number of 1's. So we return the index of the smaller row, 0, and the maximum count of ones (1). So, the answer is [0,1].
//
// Constraints:
// m == mat.length 
// 	n == mat[i].length 
// 	1 <= m, n <= 100 
// 	mat[i][j] is either 0 or 1.
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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rowAndMaximumOnes(int** mat, int matSize, int* matColSize, int* returnSize) {
    int maxRowIndex = -1;
    int maxOnesCount = -1;

    for (int i = 0; i < matSize; i++) {
        int currentOnesCount = 0;
        for (int j = 0; j < matColSize[i]; j++) {
            if (mat[i][j] == 1) {
                currentOnesCount++;
            }
        }
        if (currentOnesCount > maxOnesCount) {
            maxOnesCount = currentOnesCount;
            maxRowIndex = i;
        }
    }

    int* result = (int*)malloc(2 * sizeof(int));
    result[0] = maxRowIndex;
    result[1] = maxOnesCount;
    *returnSize = 2;

    return result;      
}
