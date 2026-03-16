// Source: https://leetcode.com/problems/pacific-atlantic-water-flow/   |   Difficulty: Medium
//
// Problem Description:
// There is an m x n rectangular island that borders both the Pacific Ocean and Atlantic Ocean. The Pacific Ocean touches the island's left and top edges, and the Atlantic Ocean touches the island's right and bottom edges.
//
// The island is partitioned into a grid of square cells. You are given an m x n integer matrix heights where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).
//
// The island receives a lot of rain, and the rain water can flow to neighboring cells directly north, south, east, and west if the neighboring cell's height is less than or equal to the current cell's height. Water can flow from any cell adjacent to an ocean into the ocean.
//
// Return a 2D list of grid coordinates result where result[i] = [ri, ci] denotes that rain water can flow from cell (ri, ci) to both the Pacific and Atlantic oceans.
//
// Example:
// Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
// Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
// Explanation: The following cells can flow to the Pacific and Atlantic oceans, as shown below:
// [0,4]: [0,4] -> Pacific Ocean 
//        [0,4] -> Atlantic Ocean
// [1,3]: [1,3] -> [0,3] -> Pacific Ocean 
//        [1,3] -> [1,4] -> Atlantic Ocean
// [1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean 
//        [1,4] -> Atlantic Ocean
// [2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean 
//        [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
// [3,0]: [3,0] -> Pacific Ocean 
//        [3,0] -> [4,0] -> Atlantic Ocean
// [3,1]: [3,1] -> [3,0] -> Pacific Ocean 
//        [3,1] -> [4,1] -> Atlantic Ocean
// [4,0]: [4,0] -> Pacific Ocean 
//        [4,0] -> Atlantic Ocean
// Note that there are other possible paths for these cells to flow to the Pacific and Atlantic oceans.
//
// Constraints:
// m == heights.length
// 	n == heights[r].length
// 	1 <= m, n <= 200
// 	0 <= heights[r][c] <= 105
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Intersection Point of Lines (geometry, number, enumeration)
//   • When to use: When you need to find the exact coordinates where two lines meet in a 2D plane, or determine if they are parallel or coincident. This is useful for geometric problems involving line segments or polygons.
//   • Idea: This method calculates the coordinates of the intersection point of two lines, typically represented in general form (Ax + By + C = 0), by solving a system of linear equations. It has a constant time complexity, O(1), for each pair of lines.
//   • Invariants: The coefficients (a, b, c) for each line remain constant throughout the calculation.; If the determinant of the coefficient matrix is non-zero, a unique intersection point exists.
//   • Tips: Represent lines in a consistent form, like general form (Ax + By + C = 0) or slope-intercept (y = mx + b).; Handle edge cases for parallel and coincident lines explicitly to avoid division by zero.
//   • Pitfalls: Division by zero if lines are parallel or coincident without proper checks.; Floating-point precision errors can lead to incorrect intersection points or misidentification of parallel lines.
// - Maximum flow - Dinic's algorithm (graph, bfs, dfs)
//   • When to use: Use Dinic's algorithm to find the maximum flow in a flow network. It is particularly efficient for dense graphs or when its polynomial time complexity is advantageous.
//   • Idea: Dinic's algorithm is a strongly polynomial time algorithm for computing the maximum flow in a flow network. It operates in phases, each involving constructing a layered network using BFS and then finding a blocking flow using DFS, achieving a time complexity of O(V^2E).
//   • Invariants: The flow pushed through any edge never exceeds its original capacity.; For any vertex other than the source or sink, the total incoming flow equals the total outgoing flow.
//   • Tips: Use BFS to construct the layered network from source to sink, ensuring shortest paths.; Implement edge pointers (current edge optimization) to efficiently skip saturated edges during DFS.
//   • Pitfalls: Incorrectly building the layered network, leading to non-shortest augmenting paths.; Failing to update residual capacities for both forward and reverse edges after pushing flow.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size();
        if (m == 0) return {};
        int n = heights[0].size();
        if (n == 0) return {};

        vector<vector<bool>> pacific(m, vector<bool>(n, false));
        vector<vector<bool>> atlantic(m, vector<bool>(n, false));

        queue<pair<int, int>> pq;
        queue<pair<int, int>> aq;

        for (int i = 0; i < m; ++i) {
            pq.push({i, 0});
            pacific[i][0] = true;
            aq.push({i, n - 1});
            atlantic[i][n - 1] = true;
        }
        for (int j = 0; j < n; ++j) {
            pq.push({0, j});
            pacific[0][j] = true;
            aq.push({m - 1, j});
            atlantic[m - 1][j] = true;
        }

        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        auto bfs = [&](queue<pair<int, int>>& q, vector<vector<bool>>& visited) {
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                for (auto& dir : directions) {
                    int nx = x + dir.first;
                    int ny = y + dir.second;
                    if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                        !visited[nx][ny] && heights[nx][ny] >= heights[x][y]) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
        };

        bfs(pq, pacific);
        bfs(aq, atlantic);

        vector<vector<int>> result;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (pacific[i][j] && atlantic[i][j]) {
                    result.push_back({i, j});
                }
            }
        }

        return result;          
    }
};
