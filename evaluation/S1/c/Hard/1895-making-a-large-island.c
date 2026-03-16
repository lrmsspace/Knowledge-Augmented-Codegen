// Source: https://leetcode.com/problems/making-a-large-island/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
//
// Return the size of the largest island in grid after applying this operation.
//
// An island is a 4-directionally connected group of 1s.
//
// Example:
// Input: grid = [[1,0],[0,1]]
// Output: 3
// Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 500
// 	grid[i][j] is either 0 or 1.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, stack, bfs, enumeration)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level. It is suitable for exploring all reachable nodes from a source in increasing order of distance.
//   • Idea: Breadth-First Search (BFS) is a graph traversal algorithm that explores all the neighbor nodes at the current depth level before moving on to nodes at the next depth level. It finds the shortest path in an unweighted graph in O(V + E) time.
//   • Invariants: All nodes currently in the queue are at the same or adjacent depth level.; All 'marked' nodes have been visited, and their 'distTo' values are the shortest path from the source.
//   • Tips: Use a queue to manage nodes to visit, ensuring level-by-level exploration.; Maintain a 'visited' array or set to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly using a stack instead of a queue will result in Depth-First Search behavior.
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
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

int largestIsland(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    int islandId = 2; // Start from 2 to avoid confusion with 0 and 1
    int* islandSizes = (int*)calloc(n * n + 2, sizeof(int));
    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    // DFS to label islands and calculate their sizes
    void dfs(int r, int c, int id) {
        if (r < 0 || r >= n || c < 0 || c >= n || grid[r][c] != 1) return;
        grid[r][c] = id;
        islandSizes[id]++;
        for (int d = 0; d < 4; d++) {
            dfs(r + directions[d][0], c + directions[d][1], id);
        }
    }

    // Label all islands
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                dfs(i, j, islandId);
                islandId++;
            }
        }
    }

    int maxIslandSize = 0;
    for (int i = 2; i < islandId; i++) {
        if (islandSizes[i] > maxIslandSize) {
            maxIslandSize = islandSizes[i];
        }
    }

    // Try converting each 0 to 1 and calculate potential island size
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                int newSize = 1; // Convert 0 to 1
                int seen[islandId];
                memset(seen, 0, sizeof(seen));
                for (int d = 0; d < 4; d++) {
                    int ni = i + directions[d][0];
                    int nj = j + directions[d][1];
                    if (ni >= 0 && ni < n && nj >= 0 && nj < n) {
                        int id = grid[ni][nj];
                        if (id > 1 && !seen[id]) {
                            newSize += islandSizes[id];
                            seen[id] = 1;
                        }
                    }
                }
                if (newSize > maxIslandSize) {
                    maxIslandSize = newSize;
                }
            }
        }
    }
    free(islandSizes);
    return maxIslandSize;    
}
