// Source: https://leetcode.com/problems/strange-printer-ii/   |   Difficulty: Hard
//
// Problem Description:
// There is a strange printer with the following two special requirements:
//
//
// 	On each turn, the printer will print a solid rectangular pattern of a single color on the grid. This will cover up the existing colors in the rectangle.
// 	Once the printer has used a color for the above operation, the same color cannot be used again.
//
//
// You are given a m x n matrix targetGrid, where targetGrid[row][col] is the color in the position (row, col) of the grid.
//
// Return true if it is possible to print the matrix targetGrid, otherwise, return false.
//
// Example:
// Input: targetGrid = [[1,1,1,1],[1,2,2,1],[1,2,2,1],[1,1,1,1]]
// Output: true
//
// Constraints:
// m == targetGrid.length
// 	n == targetGrid[i].length
// 	1 <= m, n <= 60
// 	1 <= targetGrid[row][col] <= 60
//
// Helpful references (internal KB):
// - Topological Sorting (graph, array, dfs, topo)
//   • When to use: Use for graph or tree traversal, pathfinding, cycle detection, or topological sorting in DAGs. It's also suitable for exploring all states in a search space.
//   • Idea: DFS explores as far as possible along each branch before backtracking, typically using recursion or an explicit stack. Topological sort orders nodes in a DAG such that for every directed edge u -> v, u comes before v, achievable with DFS in O(V+E) time.
//   • Invariants: All nodes reachable from the current path have been explored or are in the recursion stack.; A node is marked 'visited' only after all its descendants have been fully explored.
//   • Tips: Use a visited set/array to prevent infinite loops in graphs and redundant computations.; Recursion is natural for DFS, but an explicit stack can avoid recursion depth limits.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect results.; Exceeding recursion depth limits for very deep graphs or trees.
// - Directed Graphs (graph, stack, dfs, topo)
//   • When to use: Use when you need to traverse all reachable vertices in a directed graph, find specific vertex orderings, or determine a valid linear ordering of vertices based on dependencies. It's also used for cycle detection in directed graphs.
//   • Idea: Depth-First Search (DFS) explores as far as possible along each branch before backtracking. When applied to directed graphs, it can determine reachability, detect cycles, and compute topological orderings in O(V + E) time.
//   • Invariants: A vertex is marked visited only after all its descendants in the DFS tree have been fully explored.; If a back-edge is encountered (to a vertex currently in the recursion stack), a cycle is detected.
//   • Tips: Use a visited array/set to prevent infinite loops and redundant work.; Maintain a recursion stack or visiting array to detect cycles during DFS.
//   • Pitfalls: Forgetting to handle disconnected components in the graph.; Incorrectly implementing cycle detection, especially in directed graphs.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isPrintable(int** targetGrid, int targetGridSize, int* targetGridColSize) {
    int m = targetGridSize;
    int n = targetGridColSize[0];
    int top[61], bottom[61], left[61], right[61];
    bool exist[61];
    memset(top, 0x3f, sizeof(top));
    memset(bottom, 0, sizeof(bottom));
    memset(left, 0x3f, sizeof(left));
    memset(right, 0, sizeof(right));
    memset(exist, 0, sizeof(exist));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int color = targetGrid[i][j];
            exist[color] = true;
            if (i < top[color]) top[color] = i;
            if (i > bottom[color]) bottom[color] = i;
            if (j < left[color]) left[color] = j;
            if (j > right[color]) right[color] = j;
        }
    }

    bool changed;
    do {
        changed = false;
        for (int color = 1; color <= 60; color++) {
            if (!exist[color]) continue;
            for (int i = top[color]; i <= bottom[color]; i++) {
                for (int j = left[color]; j <= right[color]; j++) {
                    if (targetGrid[i][j] != color && targetGrid[i][j] != 0) {
                        changed = true;
                        targetGrid[i][j] = 0;
                    }
                }
            }
        }
    } while (changed);

    for (int color = 1; color <= 60; color++) {
        if (!exist[color]) continue;
        for (int i = top[color]; i <= bottom[color]; i++) {
            for (int j = left[color]; j <= right[color]; j++) {
                if (targetGrid[i][j] != 0) {
                    return false;
                }
            }
        }
    }

    return true;        
}
