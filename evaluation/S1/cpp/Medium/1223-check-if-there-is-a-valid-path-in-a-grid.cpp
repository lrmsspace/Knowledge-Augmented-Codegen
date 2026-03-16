// Source: https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n grid. Each cell of grid represents a street. The street of grid[i][j] can be:
//
//
// 	1 which means a street connecting the left cell and the right cell.
// 	2 which means a street connecting the upper cell and the lower cell.
// 	3 which means a street connecting the left cell and the lower cell.
// 	4 which means a street connecting the right cell and the lower cell.
// 	5 which means a street connecting the left cell and the upper cell.
// 	6 which means a street connecting the right cell and the upper cell.
//
//
// You will initially start at the street of the upper-left cell (0, 0). A valid path in the grid is a path that starts from the upper left cell (0, 0) and ends at the bottom-right cell (m - 1, n - 1). The path should only follow the streets.
//
// Notice that you are not allowed to change any street.
//
// Return true if there is a valid path in the grid or false otherwise.
//
// Example:
// Input: grid = [[2,4,3],[6,5,2]]
// Output: true
// Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 300
// 	1 <= grid[i][j] <= 6
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool hasValidPath(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Directions: up, right, down, left
        vector<pair<int, int>> directions = {{-1,0}, {0,1}, {1,0}, {0,-1}};
        // Map street type to possible directions
        unordered_map<int, vector<int>> streetDirs = {
            {1, {3, 1}}, // left, right
            {2, {0, 2}}, // up, down
            {3, {2, 3}}, // down, left
            {4, {2, 1}}, // down, right
            {5, {0, 3}}, // up, left
            {6, {0, 1}}  // up, right
        };

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        queue<pair<int, int>> q;
        q.push({0, 0});
        visited[0][0] = true;

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            if (x == m - 1 && y == n - 1) return true;

            for (int dir : streetDirs[grid[x][y]]) {
                int nx = x + directions[dir].first;
                int ny = y + directions[dir].second;

                if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
                    // Check if the next cell can connect back to the current cell
                    for (int nextDir : streetDirs[grid[nx][ny]]) {
                        if ((dir + 2) % 4 == nextDir) {
                            visited[nx][ny] = true;
                            q.push({nx, ny});
                            break;
                        }
                    }
                }
            }
        }

        return false;           
    }
};
