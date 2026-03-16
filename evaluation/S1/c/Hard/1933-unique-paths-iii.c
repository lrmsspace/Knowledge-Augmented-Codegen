// Source: https://leetcode.com/problems/unique-paths-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer array grid where grid[i][j] could be:
//
//
// 	1 representing the starting square. There is exactly one starting square.
// 	2 representing the ending square. There is exactly one ending square.
// 	0 representing empty squares we can walk over.
// 	-1 representing obstacles that we cannot walk over.
//
//
// Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.
//
// Example:
// Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
// Output: 2
// Explanation: We have the following two paths: 
// 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
// 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 20
// 	1 <= m * n <= 20
// 	-1 <= grid[i][j] <= 2
// 	There is exactly one starting cell and one ending cell.
//
// Helpful references (internal KB):
// - Depth-first search (graph, array, dfs, biconnected-components)
//   • When to use: Use when exploring all reachable nodes from a starting point, finding paths, or detecting cycles in a graph. It's suitable for problems requiring a deep, exhaustive search.
//   • Idea: Depth-first search is an algorithm for traversing or searching tree or graph data structures. It explores as far as possible along each branch before backtracking, typically running in O(V + E) time for graphs represented with adjacency lists.
//   • Invariants: Every node `v` is visited exactly once.; When `dfs(G, u, v)` is called, `v` is unvisited and `u` is its immediate predecessor in the current path.
//   • Tips: Maintain a visited set/array to avoid revisiting nodes and infinite loops.; Pass the parent node in recursive calls to correctly identify back-edges for cycle detection.
//   • Pitfalls: Failing to mark nodes as visited can lead to infinite loops in cyclic graphs.; Deep recursion can cause stack overflow errors on large graphs; use an iterative approach if needed.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int uniquePathsIII(int** grid, int gridSize, int* gridColSize) {
    int emptyCount = 0;
    int startX = -1, startY = -1;
    int endX = -1, endY = -1;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == 0) {
                emptyCount++;
            } else if (grid[i][j] == 1) {
                startX = i;
                startY = j;
            } else if (grid[i][j] == 2) {
                endX = i;
                endY = j;
            }
        }
    }

    int pathCount = 0;
    void dfs(int x, int y, int remain) {
        if (x < 0 || x >= gridSize || y < 0 || y >= gridColSize[0] || grid[x][y] == -1) {
            return;
        }
        if (x == endX && y == endY) {
            if (remain == -1) {
                pathCount++;
            }
            return;
        }

        int temp = grid[x][y];
        grid[x][y] = -1; // mark as visited

        dfs(x + 1, y, remain - 1);
        dfs(x - 1, y, remain - 1);
        dfs(x, y + 1, remain - 1);
        dfs(x, y - 1, remain - 1);

        grid[x][y] = temp; // backtrack
    }

    dfs(startX, startY, emptyCount);
    return pathCount;       
}
