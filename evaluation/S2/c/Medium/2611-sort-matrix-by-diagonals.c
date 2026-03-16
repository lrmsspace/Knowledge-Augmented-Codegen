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
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Delaunay triangulation and Voronoi diagram (geometry, graph, divide-and-conquer, sweep-line)
//   • When to use: Use this algorithm to construct a Delaunay triangulation or Voronoi diagram for a set of points in a plane. It is particularly effective for problems requiring these fundamental geometric structures.
//   • Idea: This algorithm constructs a Delaunay triangulation by recursively dividing the set of points, triangulating subproblems, and then merging the results. The merge step involves adding 'cross edges' using a sweep-line-like approach, ensuring the Delaunay property is maintained, typically achieving O(N log N) time complexity.
//   • Invariants: All points in the left sub-triangulation are to the left of all points in the right sub-triangulation.; Each sub-triangulation (left and right) is a valid Delaunay triangulation for its respective point set.
//   • Tips: Sorting points by x-coordinate (and y for ties) is fundamental for the divide-and-conquer strategy.; The quad-edge data structure simplifies topological operations like adding or deleting edges and faces.
//   • Pitfalls: Degenerate cases, such as collinear points or cocircular points, require robust handling to prevent errors.; Implementing the quad-edge data structure and its operations correctly can be complex and error-prone.
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
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

    // Sort bottom-left triangle diagonals in non-increasing order
    for (int d = 0; d < n; d++) {
        int* diagonal = (int*)malloc((n - d) * sizeof(int));
        int idx = 0;
        for (int i = d, j = 0; i < n && j < n; i++, j++) {
            diagonal[idx++] = grid[i][j];
        }
        qsort(diagonal, idx, sizeof(int), (int(*)(const void*, const void*))cmp_desc);
        idx = 0;
        for (int i = d, j = 0; i < n && j < n; i++, j++) {
            result[i][j] = diagonal[idx++];
        }
        free(diagonal);
    }

    // Sort top-right triangle diagonals in non-decreasing order
    for (int d = 1; d < n; d++) {
        int* diagonal = (int*)malloc((n - d) * sizeof(int));
        int idx = 0;
        for (int i = 0, j = d; i < n && j < n; i++, j++) {
            diagonal[idx++] = grid[i][j];
        }
        qsort(diagonal, idx, sizeof(int), (int(*)(const void*, const void*))cmp_asc);
        idx = 0;
        for (int i = 0, j = d; i < n && j < n; i++, j++) {
            result[i][j] = diagonal[idx++];
        }
        free(diagonal);
    }

    *returnSize = n;
    return result;      
}
