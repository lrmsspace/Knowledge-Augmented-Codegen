// Source: https://leetcode.com/problems/construct-2d-grid-matching-graph-layout/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array edges representing an undirected graph having n nodes, where edges[i] = [ui, vi] denotes an edge between nodes ui and vi.
//
// Construct a 2D grid that satisfies these conditions:
//
//
// 	The grid contains all nodes from 0 to n - 1 in its cells, with each node appearing exactly once.
// 	Two nodes should be in adjacent grid cells (horizontally or vertically) if and only if there is an edge between them in edges.
//
//
// It is guaranteed that edges can form a 2D grid that satisfies the conditions.
//
// Return a 2D integer array satisfying the conditions above. If there are multiple solutions, return any of them.
//
// Example:
// Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]]
//
// Output: [[3,1],[2,0]]
//
// Explanation:
//
// Constraints:
// 2 <= n <= 5 * 104
// 	1 <= edges.length <= 105
// 	edges[i] = [ui, vi]
// 	0 <= ui < vi < n
// 	All the edges are distinct.
// 	The input is generated such that edges can form a 2D grid that satisfies the conditions.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** constructGridLayout(int n, int** edges, int edgesSize, int* edgesColSize, int* returnSize, int** returnColumnSizes) {
    if (!returnSize || !returnColumnSizes) return NULL;
    *returnSize = 0;
    *returnColumnSizes = NULL;
    if (n <= 0) return NULL;

    /* Since the problem guarantees a valid grid layout, we can deduce the grid dimensions.
       The grid must be rectangular and contain all n nodes. We can find factors of n to determine rows and columns. */
    int rows = 0, cols = 0;
    for (int i = 1; i * i <= n; ++i) {
        if (n % i == 0) {
            rows = i;
            cols = n / i;
        }
    }

    /* Allocate the grid */
    int **grid = (int**)malloc(rows * sizeof(int*));
    if (!grid) return NULL;
    for (int i = 0; i < rows; ++i) {
        grid[i] = (int*)malloc(cols * sizeof(int));
        if (!grid[i]) {
            for (int j = 0; j < i; ++j) free(grid[j]);
            free(grid);
            return NULL;
        }
    }

    /* Fill the grid in a simple row-major order */
    for (int i = 0; i < n; ++i) {
        grid[i / cols][i % cols] = i;
    }

    *returnSize = rows;
    *returnColumnSizes = (int*)malloc(rows * sizeof(int));
    if (!*returnColumnSizes) {
        for (int i = 0; i < rows; ++i) free(grid[i]);
        free(grid);
        return NULL;
    }
    for (int i = 0; i < rows; ++i) {
        (*returnColumnSizes)[i] = cols;
    }

    return grid;        
}
