// Source: https://leetcode.com/problems/swim-in-rising-water/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).
//
// It starts raining, and water gradually rises over time. At time t, the water level is t, meaning any cell with elevation less than equal to t is submerged or reachable.
//
// You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.
//
// Return the minimum time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).
//
// Example:
// Input: grid = [[0,2],[1,3]]
// Output: 3
// Explanation:
// At time 0, you are in grid location (0, 0).
// You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
// You cannot reach point (1, 1) until time 3.
// When the depth of water is 3, we can swim anywhere inside the grid.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 50
// 	0 <= grid[i][j] < n2
// 	Each value grid[i][j] is unique.
//
// Helpful references (internal KB):
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
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
    int swimInWater(vector<vector<int>>& grid) {
        int n = grid.size();
        int left = grid[0][0], right = n * n - 1;
        vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        
        auto canReachEnd = [&](int t) {
            vector<vector<bool>> visited(n, vector<bool>(n, false));
            queue<pair<int, int>> q;
            if (grid[0][0] <= t) {
                q.push({0, 0});
                visited[0][0] = true;
            }
            
            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                if (x == n - 1 && y == n - 1) return true;
                
                for (auto& dir : directions) {
                    int nx = x + dir[0], ny = y + dir[1];
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny] && grid[nx][ny] <= t) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
            return false;
        };
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (canReachEnd(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        
        return left;            
    }
};
