// Source: https://leetcode.com/problems/first-completely-painted-row-or-column/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array arr, and an m x n integer matrix mat. arr and mat both contain all the integers in the range [1, m * n].
//
// Go through each index i in arr starting from index 0 and paint the cell in mat containing the integer arr[i].
//
// Return the smallest index i at which either a row or a column will be completely painted in mat.
//
// Example:
// Input: arr = [1,3,4,2], mat = [[1,4],[2,3]]
// Output: 2
// Explanation: The moves are shown in order, and both the first row and second column of the matrix become fully painted at arr[2].
//
// Constraints:
// m == mat.length
// 	n = mat[i].length
// 	arr.length == m * n
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	1 <= arr[i], mat[r][c] <= m * n
// 	All the integers of arr are unique.
// 	All the integers of mat are unique.
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Lowest Common Ancestor (array, sparse-table)
//   • When to use: Use this when you need to find the lowest common ancestor of many pairs of nodes in a static tree efficiently. It excels in scenarios with numerous queries after initial setup.
//   • Idea: This technique finds the LCA by transforming the problem into a Range Minimum Query (RMQ) on an Euler tour of the tree. It achieves O(N log N) precomputation time and O(1) query time.
//   • Invariants: The sparse_table[k][i] stores the minimum depth in the Euler tour array segment starting at index i and spanning 2^k elements.; The first_occurrence array correctly maps each node to its initial appearance index in the Euler tour.
//   • Tips: Perform an Euler tour (DFS traversal) to linearize the tree into an array of nodes and their depths.; Store the first occurrence index of each node in the Euler tour array.
//   • Pitfalls: Off-by-one errors when calculating range lengths or sparse table indices.; Incorrectly handling the Euler tour array, especially when mapping back to original nodes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int firstCompleteIndex(int* arr, int arrSize, int** mat, int matSize, int* matColSize) {
    int m = matSize, n = matColSize[0];
    int* rowCount = (int*)calloc(m, sizeof(int));
    int* colCount = (int*)calloc(n, sizeof(int));
    int* position = (int*)malloc((m * n + 1) * sizeof(int));

    // Map each value to its position in the matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            position[mat[i][j]] = i * n + j;
        }
    }

    // Iterate through arr and paint the cells
    for (int i = 0; i < arrSize; i++) {
        int pos = position[arr[i]];
        int r = pos / n;
        int c = pos % n;

        rowCount[r]++;
        colCount[c]++;

        // Check if the current row or column is completely painted
        if (rowCount[r] == n || colCount[c] == m) {
            free(rowCount);
            free(colCount);
            free(position);
            return i; // Return the index at which a row or column is completely painted
        }
    }

    free(rowCount);
    free(colCount);
    free(position);
    return -1; // Return -1 if no row or column is completely painted       
}
