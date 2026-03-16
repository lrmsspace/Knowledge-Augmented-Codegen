// Source: https://leetcode.com/problems/count-sub-islands/   |   Difficulty: Medium
//
// Problem Description:
// You are given two m x n binary matrices grid1 and grid2 containing only 0's (representing water) and 1's (representing land). An island is a group of 1's connected 4-directionally (horizontal or vertical). Any cells outside of the grid are considered water cells.
//
// An island in grid2 is considered a sub-island if there is an island in grid1 that contains all the cells that make up this island in grid2.
//
// Return the number of islands in grid2 that are considered sub-islands.
//
// Example:
// Input: grid1 = [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]], grid2 = [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]
// Output: 3
// Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
// The 1s colored red in grid2 are those considered to be part of a sub-island. There are three sub-islands.
//
// Constraints:
// m == grid1.length == grid2.length
// 	n == grid1[i].length == grid2[i].length
// 	1 <= m, n <= 500
// 	grid1[i][j] and grid2[i][j] are either 0 or 1.
//
// Helpful references (internal KB):
// - Directed Graphs (graph, matrix, dfs)
//   • When to use: Use when needing to determine reachability between all pairs of vertices in a directed graph, especially for small or dense graphs where O(V*(V+E)) time is acceptable.
//   • Idea: This approach determines all-pairs reachability in a directed graph by performing a Depth-First Search starting from each vertex. It has a time complexity of O(V*(V+E)) and a space complexity of O(V^2).
//   • Invariants: For any vertex u, after its dedicated DFS completes, TC[u][v] is true for all v reachable from u.; The transitive closure matrix TC accurately reflects all-pairs reachability in the original graph.
//   • Tips: Initialize a boolean matrix to store reachability results.; For each vertex, perform a full DFS to mark all nodes reachable from it.
//   • Pitfalls: High time complexity O(V*(V+E)) makes it unsuitable for large sparse graphs.; High space complexity O(V^2) can be prohibitive for graphs with many vertices.
// - Search for connected components in a graph (graph, dfs, bfs, enumeration)
//   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
//   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
//   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
//   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
//   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private boolean isSubIsland(int[][] grid1, int[][] grid2, boolean[][] visited, int r, int c) {
        int rows = grid2.length;
        int cols = grid2[0].length;

        if (r < 0 || r >= rows || c < 0 || c >= cols || grid2[r][c] == 0 || visited[r][c]) {
            return true;
        }

        visited[r][c] = true;

        boolean isSub = true;
        if (grid1[r][c] == 0) {
            isSub = false;
        }

        isSub &= isSubIsland(grid1, grid2, visited, r + 1, c);
        isSub &= isSubIsland(grid1, grid2, visited, r - 1, c);
        isSub &= isSubIsland(grid1, grid2, visited, r, c + 1);
        isSub &= isSubIsland(grid1, grid2, visited, r, c - 1);

        return isSub;
    }
    public int countSubIslands(int[][] grid1, int[][] grid2) {
        int rows = grid2.length;
        int cols = grid2[0].length;
        boolean[][] visited = new boolean[rows][cols];
        int subIslandCount = 0;

        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid2[r][c] == 1 && !visited[r][c]) {
                    if (isSubIsland(grid1, grid2, visited, r, c)) {
                        subIslandCount++;
                    }
                }
            }
        }

        return subIslandCount;          
    }
}
