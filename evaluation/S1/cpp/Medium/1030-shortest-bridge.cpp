// Source: https://leetcode.com/problems/shortest-bridge/   |   Difficulty: Medium
//
// Problem Description:
// You are given an n x n binary matrix grid where 1 represents land and 0 represents water.
//
// An island is a 4-directionally connected group of 1's not connected to any other 1's. There are exactly two islands in grid.
//
// You may change 0's to 1's to connect the two islands to form one island.
//
// Return the smallest number of 0's you must flip to connect the two islands.
//
// Example:
// Input: grid = [[0,1],[1,0]]
// Output: 1
//
// Constraints:
// n == grid.length == grid[i].length
// 	2 <= n <= 100
// 	grid[i][j] is either 0 or 1.
// 	There are exactly two islands in grid.
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Strong Orientation (graph, dfs, biconnected-components)
//   • When to use: Use when you need to identify maximal subgraphs where removing any single vertex does not disconnect the subgraph. This is crucial for analyzing network robustness and fault tolerance.
//   • Idea: This algorithm decomposes a graph into maximal 2-vertex-connected subgraphs, meaning removing any single vertex does not disconnect them. It uses DFS to identify articulation points and bridges, achieving O(V+E) time complexity.
//   • Invariants: All edges on the DFS stack form part of a potential BCC.; A vertex's low-link value is the minimum discovery time reachable from it (including itself) through its DFS subtree and at most one back-edge.
//   • Tips: Maintain discovery times and low-link values for each vertex.; Use a stack to store edges or vertices of the current DFS path.
//   • Pitfalls: Incorrectly calculating low-link values, especially for back-edges.; Missing the root node articulation point condition (at least two children in DFS tree).
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        queue<pair<int, int>> q;

        // DFS to find and mark the first island
        function<void(int, int)> dfs = [&](int x, int y) {
            if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] != 1) return;
            grid[x][y] = 2; // Mark as visited
            q.push({x, y});
            for (auto& dir : directions) {
                dfs(x + dir.first, y + dir.second);
            }
        };

        // Find the first island and start DFS
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (found) break;
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    dfs(i, j);
                    found = true;
                    break;
                }
            }
        }

        // BFS to expand from the first island and find the shortest path to the second island
        int steps = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                auto [x, y] = q.front();
                q.pop();
                for (auto& dir : directions) {
                    int nx = x + dir.first;
                    int ny = y + dir.second;
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                        if (grid[nx][ny] == 1) {
                            return steps; // Found the second island
                        } else if (grid[nx][ny] == 0) {
                            grid[nx][ny] = 2; // Mark as visited
                            q.push({nx, ny});
                        }
                    }
                }
            }
            ++steps;
        }

        return -1; // Should never reach here           
    }
};      
