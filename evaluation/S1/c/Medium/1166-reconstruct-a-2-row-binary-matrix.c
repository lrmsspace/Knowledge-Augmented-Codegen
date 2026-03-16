// Source: https://leetcode.com/problems/reconstruct-a-2-row-binary-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given the following details of a matrix with n columns and 2 rows :
//
//
// 	The matrix is a binary matrix, which means each element in the matrix can be 0 or 1.
// 	The sum of elements of the 0-th(upper) row is given as upper.
// 	The sum of elements of the 1-st(lower) row is given as lower.
// 	The sum of elements in the i-th column(0-indexed) is colsum[i], where colsum is given as an integer array with length n.
//
//
// Your task is to reconstruct the matrix with upper, lower and colsum.
//
// Return it as a 2-D integer array.
//
// If there are more than one valid solution, any of them will be accepted.
//
// If no valid solution exists, return an empty 2-D array.
//
// Example:
// Input: upper = 2, lower = 1, colsum = [1,1,1]
// Output: [[1,1,0],[0,0,1]]
// Explanation: [[1,0,1],[0,1,0]], and [[0,1,1],[1,0,0]] are also correct answers.
//
// Constraints:
// 1 <= colsum.length <= 10^5
// 	0 <= upper, lower <= colsum.length
// 	0 <= colsum[i] <= 2
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Hungarian algorithm for solving the assignment problem (matrix, graph, array, greedy, bfs, enumeration)
//   • When to use: Use when finding a minimum cost perfect matching in a bipartite graph, typically represented as an N x N cost matrix, where each row must be assigned to exactly one column.
//   • Idea: The Hungarian algorithm finds a minimum weight perfect matching in a bipartite graph, solving the assignment problem for an N x N cost matrix. It iteratively finds augmenting paths in an equality graph and adjusts potentials, achieving O(N^3) time complexity.
//   • Invariants: For all i, j, u[i] + v[j] <= A[i][j] (potential condition).; The current matching is always valid (each row/column used at most once).
//   • Tips: Understand the concept of potentials and their role in maintaining the equality graph.; The algorithm can be adapted for maximum profit problems by negating costs.
//   • Pitfalls: Incorrectly updating potentials can lead to non-optimal solutions or infinite loops.; Handling non-square matrices requires careful padding with dummy values.
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
int** reconstructMatrix(int upper, int lower, int* colsum, int colsumSize, int* returnSize, int** returnColumnSizes) {
    int** result = (int**)malloc(2 * sizeof(int*));
    result[0] = (int*)calloc(colsumSize, sizeof(int));
    result[1] = (int*)calloc(colsumSize, sizeof(int));
    *returnColumnSizes = (int*)malloc(2 * sizeof(int));
    (*returnColumnSizes)[0] = colsumSize;
    (*returnColumnSizes)[1] = colsumSize;
    *returnSize = 2;

    for (int i = 0; i < colsumSize; i++) {
        if (colsum[i] == 2) {
            if (upper > 0 && lower > 0) {
                result[0][i] = 1;
                result[1][i] = 1;
                upper--;
                lower--;
            } else {
                // Not enough upper or lower to satisfy colsum[i] == 2
                free(result[0]);
                free(result[1]);
                free(result);
                free(*returnColumnSizes);
                *returnSize = 0;
                return NULL;
            }
        }
    }

    for (int i = 0; i < colsumSize; i++) {
        if (colsum[i] == 1) {
            if (upper > 0) {
                result[0][i] = 1;
                upper--;
            } else if (lower > 0) {
                result[1][i] = 1;
                lower--;
            } else {
                // Not enough upper or lower to satisfy colsum[i] == 1
                free(result[0]);
                free(result[1]);
                free(result);
                free(*returnColumnSizes);
                *returnSize = 0;
                return NULL;
            }
        }
    }

    if (upper != 0 || lower != 0) {
        // Not all upper or lower have been used
        free(result[0]);
        free(result[1]);
        free(result);
        free(*returnColumnSizes);
        *returnSize = 0;
        return NULL;
    }

    return result;      
}
