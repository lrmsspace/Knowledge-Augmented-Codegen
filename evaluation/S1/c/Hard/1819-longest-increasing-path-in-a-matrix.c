// Source: https://leetcode.com/problems/longest-increasing-path-in-a-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n integers matrix, return the length of the longest increasing path in matrix.
//
// From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).
//
// Example:
// Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
// Output: 4
// Explanation: The longest increasing path is [1, 2, 6, 9].
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 200
// 	0 <= matrix[i][j] <= 231 - 1
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Depth-first search (graph, array, stack, dfs)
//   • When to use: Use DFS when you need to explore all reachable nodes from a starting point, find paths, detect cycles, or perform topological sorting in a graph. It is suitable for problems requiring deep exploration before backtracking.
//   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically running in O(V + E) time for graphs.
//   • Invariants: All nodes currently on the recursion stack (or explicit stack) are part of the current path from the source.; Once a node `v` is marked `visited`, it will not be processed again by the main traversal logic.
//   • Tips: Use a `visited` array or set to track explored nodes.; Pass the parent node in recursive calls to correctly detect cycles.
//   • Pitfalls: Risk of stack overflow for very deep graphs with recursive implementations.; Failure to use a `visited` array leads to infinite loops in cyclic graphs.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0 || matrixColSize[0] == 0) return 0;

    int rows = matrixSize;
    int cols = matrixColSize[0];
    int **dp = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        dp[i] = (int *)calloc(cols, sizeof(int));
    }

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int dfs(int r, int c) {
        if (dp[r][c] != 0) return dp[r][c];

        int maxLength = 1;
        for (int d = 0; d < 4; d++) {
            int nr = r + directions[d][0];
            int nc = c + directions[d][1];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && matrix[nr][nc] > matrix[r][c]) {
                int length = 1 + dfs(nr, nc);
                if (length > maxLength) {
                    maxLength = length;
                }
            }
        }
        dp[r][c] = maxLength;
        return maxLength;
    }

    int longestPath = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int pathLength = dfs(i, j);
            if (pathLength > longestPath) {
                longestPath = pathLength;
            }
        }
    }

    for (int i = 0; i < rows; i++) {
        free(dp[i]);
    }
    free(dp);

    return longestPath;     
}
