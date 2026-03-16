// Source: https://leetcode.com/problems/maximum-number-of-fish-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D matrix grid of size m x n, where (r, c) represents:
//
//
// 	A land cell if grid[r][c] = 0, or
// 	A water cell containing grid[r][c] fish, if grid[r][c] > 0.
//
//
// A fisher can start at any water cell (r, c) and can do the following operations any number of times:
//
//
// 	Catch all the fish at cell (r, c), or
// 	Move to any adjacent water cell.
//
//
// Return the maximum number of fish the fisher can catch if he chooses his starting cell optimally, or 0 if no water cell exists.
//
// An adjacent cell of the cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) or (r - 1, c) if it exists.
//
// Example:
// Input: grid = [[0,2,1,0],[4,0,0,3],[1,0,0,4],[0,3,2,0]]
// Output: 7
// Explanation: The fisher can start at cell (1,3) and collect 3 fish, then move to cell (2,3) and collect 4 fish.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 10
// 	0 <= grid[i][j] <= 10
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Search for connected components in a graph (graph, dfs, bfs, enumeration)
//   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
//   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
//   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
//   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
//   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
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
    int findMaxFish(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        int maxFish = 0;

        // Directions for moving up, down, left, right
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0 && !visited[i][j]) {
                    // Start BFS from this water cell
                    int currentFish = 0;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    visited[i][j] = true;

                    while (!q.empty()) {
                        auto [x, y] = q.front();
                        q.pop();
                        currentFish += grid[x][y];

                        // Explore all 4 directions
                        for (auto& dir : directions) {
                            int newX = x + dir.first;
                            int newY = y + dir.second;

                            // Check bounds and if it's a water cell and not visited
                            if (newX >= 0 && newX < m && newY >= 0 && newY < n &&
                                grid[newX][newY] > 0 && !visited[newX][newY]) {
                                visited[newX][newY] = true;
                                q.push({newX, newY});
                            }
                        }
                    }

                    maxFish = max(maxFish, currentFish);
                }
            }
        }

        return maxFish;         
    }
};
