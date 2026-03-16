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
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
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
    int ansRows = m - k + 1, ansCols = n - k + 1;

    // Allocate memory for the answer and column sizes
    int** ans = (int**)malloc(ansRows * sizeof(int*));
    *returnColumnSizes = (int*)malloc(ansRows * sizeof(int));
    for (int i = 0; i < ansRows; i++) {
        ans[i] = (int*)malloc(ansCols * sizeof(int));
        (*returnColumnSizes)[i] = ansCols;
    }
    *returnSize = ansRows;

    // Compute minimum absolute difference for each k x k submatrix
    for (int i = 0; i < ansRows; i++) {
        for (int j = 0; j < ansCols; j++) {
            // Use a hash set to store distinct values in the submatrix
            int distinctValues[200001]; // To handle values from -10^5 to 10^5
            int countDistinct = 0;

            for (int x = i; x < i + k; x++) {
                for (int y = j; y < j + k; y++) {
                    int val = grid[x][y] + 100000; // Shift to non-negative index
                    if (distinctValues[val] == 0) {
                        distinctValues[val] = 1;
                        countDistinct++;
                    }
                }
            }

            if (countDistinct <= 1) {
                ans[i][j] = 0; // All values are the same
            } else {
                // Find the minimum absolute difference between distinct values
                int minDiff = INT_MAX;
                for (int v1 = 0; v1 <= 200000; v1++) {
                    if (distinctValues[v1]) {
                        for (int v2 = v1 + 1; v2 <= 200000; v2++) {
                            if (distinctValues[v2]) {
                                int diff = abs((v1 - 100000) - (v2 - 100000));
                                if (diff < minDiff) {
                                    minDiff = diff;
                                }
                            }
                        }
                    }
                }
                ans[i][j] = minDiff;
            }
        }
    }

    return ans;     
}
