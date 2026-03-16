// Source: https://leetcode.com/problems/minimum-absolute-difference-in-sliding-submatrix/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid and an integer k.
//
// For every contiguous k x k submatrix of grid, compute the minimum absolute difference between any two distinct values within that submatrix.
//
// Return a 2D array ans of size (m - k + 1) x (n - k + 1), where ans[i][j] is the minimum absolute difference in the submatrix whose top-left corner is (i, j) in grid.
//
// Note: If all elements in the submatrix have the same value, the answer will be 0.
// A submatrix (x1, y1, x2, y2) is a matrix that is formed by choosing all cells matrix[x][y] where x1 <= x <= x2 and y1 <= y <= y2.
//
// Example:
// Input: grid = [[1,8],[3,-2]], k = 2
//
// Output: [[2]]
//
// Explanation:
//
//
// 	There is only one possible k x k submatrix: [[1, 8], [3, -2]].
// 	Distinct values in the submatrix are [1, 8, 3, -2].
// 	The minimum absolute difference in the submatrix is |1 - 3| = 2. Thus, the answer is [[2]].
//
// Constraints:
// 1 <= m == grid.length <= 30
// 	1 <= n == grid[i].length <= 30
// 	-105 <= grid[i][j] <= 105
// 	1 <= k <= min(m, n)
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Minimum spanning tree - Prim's algorithm (graph, heap, array, mst-prim, greedy, heap-select)
//   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, weighted graph. It is efficient for both dense graphs (O(V^2)) and sparse graphs (O(E log V)) depending on the implementation.
//   • Idea: Prim's algorithm is a greedy algorithm that builds an MST by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside the tree. It has a time complexity of O(V^2) for dense graphs using an adjacency matrix or O(E log V) for sparse graphs using a priority queue.
//   • Invariants: All selected vertices and edges form a connected component of the final MST.; For any unselected vertex `v`, `min_e[v]` stores the minimum weight of an edge connecting `v` to the currently selected component.
//   • Tips: For dense graphs, an O(V^2) implementation using an an adjacency matrix and simple array scans is efficient.; For sparse graphs, use a priority queue (min-heap) with an adjacency list to achieve O(E log V) complexity.
//   • Pitfalls: Incorrectly updating the `min_e` array or priority queue entries can lead to an incorrect MST or performance issues.; Forgetting to mark vertices as 'selected' can lead to cycles or infinite loops.
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
int** minAbsDiff(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes) {
    int m = gridSize, n = gridColSize[0];
    int out_rows = m - k + 1, out_cols = n - k + 1;

    // Allocate output array
    int** output = (int**)malloc(out_rows * sizeof(int*));
    *returnColumnSizes = (int*)malloc(out_rows * sizeof(int));
    for (int i = 0; i < out_rows; i++) {
        output[i] = (int*)malloc(out_cols * sizeof(int));
        (*returnColumnSizes)[i] = out_cols;
    }
    *returnSize = out_rows;

    // Process each k x k submatrix
    for (int i = 0; i <= m - k; i++) {
        for (int j = 0; j <= n - k; j++) {
            // Use a frequency array to track distinct values in the submatrix
            int freq[200001] = {0}; // Range from -100000 to 100000
            for (int x = 0; x < k; x++) {
                for (int y = 0; y < k; y++) {
                    freq[grid[i + x][j + y] + 100000]++;
                }
            }

            // Find the minimum absolute difference
            int prev = -1;
            int min_diff = 200001; // Larger than any possible difference
            for (int val = 0; val <= 200000; val++) {
                if (freq[val] > 0) {
                    if (prev != -1) {
                        int diff = val - prev;
                        if (diff < min_diff) {
                            min_diff = diff;
                        }
                    }
                    prev = val;
                }
            }

            // If all elements are the same, min_diff remains large, set to 0
            if (min_diff == 200001) {
                min_diff = 0;
            }

            output[i][j] = min_diff;
        }
    }

    return output;      
}
