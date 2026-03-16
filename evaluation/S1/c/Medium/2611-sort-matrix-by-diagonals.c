// Source: https://leetcode.com/problems/sort-matrix-by-diagonals/   |   Difficulty: Medium
//
// Problem Description:
// You are given an n x n square matrix of integers grid. Return the matrix such that:
//
//
// 	The diagonals in the bottom-left triangle (including the middle diagonal) are sorted in non-increasing order.
// 	The diagonals in the top-right triangle are sorted in non-decreasing order.
//
// Example:
// Input: grid = [[1,7,3],[9,8,2],[4,5,6]]
//
// Output: [[8,2,3],[9,6,7],[4,5,1]]
//
// Explanation:
//
//
//
// The diagonals with a black arrow (bottom-left triangle) should be sorted in non-increasing order:
//
//
// 	[1, 8, 6] becomes [8, 6, 1].
// 	[9, 5] and [4] remain unchanged.
//
//
// The diagonals with a blue arrow (top-right triangle) should be sorted in non-decreasing order:
//
//
// 	[7, 2] becomes [2, 7].
// 	[3] remains unchanged.
//
// Constraints:
// grid.length == grid[i].length == n
// 	1 <= n <= 10
// 	-105 <= grid[i][j] <= 105
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, especially for large datasets or external sorting where data might not fit in memory.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and requires O(N) auxiliary space.
//   • Invariants: The elements `index[lo...k-1]` are sorted and contain the smallest `k-lo` elements from the original `aux[lo...mid]` and `aux[mid+1...hi]` segments.; Pointer `i` always indicates the next element to consider from the left sorted sub-array (`aux[lo...mid]`).
//   • Tips: Implement the merge step carefully to ensure stability.; Consider an iterative bottom-up approach to avoid recursion overhead.
//   • Pitfalls: High auxiliary space complexity (O(N)) can be a concern for memory-constrained systems.; Recursive calls can lead to stack overflow for very large inputs without tail call optimization.
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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
int** sortMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int n = gridSize;
    int** result = (int**)malloc(n * sizeof(int*));
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        result[i] = (int*)malloc(n * sizeof(int));
        (*returnColumnSizes)[i] = n;
    }
    *returnSize = n;

    // Process bottom-left triangle diagonals (including main diagonal)
    for (int startRow = n - 1; startRow >= 0; startRow--) {
        int diagSize = n - startRow;
        int* diagonal = (int*)malloc(diagSize * sizeof(int));
        for (int i = 0; i < diagSize; i++) {
            diagonal[i] = grid[startRow + i][i];
        }
        // Sort in non-increasing order
        for (int i = 0; i < diagSize - 1; i++) {
            for (int j = 0; j < diagSize - i - 1; j++) {
                if (diagonal[j] < diagonal[j + 1]) {
                    int temp = diagonal[j];
                    diagonal[j] = diagonal[j + 1];
                    diagonal[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < diagSize; i++) {
            result[startRow + i][i] = diagonal[i];
        }
        free(diagonal);
    }

    // Process top-right triangle diagonals
    for (int startCol = 1; startCol < n; startCol++) {
        int diagSize = n - startCol;
        int* diagonal = (int*)malloc(diagSize * sizeof(int));
        for (int i = 0; i < diagSize; i++) {
            diagonal[i] = grid[i][startCol + i];
        }
        // Sort in non-decreasing order
        for (int i = 0; i < diagSize - 1; i++) {
            for (int j = 0; j < diagSize - i - 1; j++) {
                if (diagonal[j] > diagonal[j + 1]) {
                    int temp = diagonal[j];
                    diagonal[j] = diagonal[j + 1];
                    diagonal[j + 1] = temp;
                }
            }
        }
        for (int i = 0; i < diagSize; i++) {
            result[i][startCol + i] = diagonal[i];
        }
        free(diagonal);
    }
    return result;
}
