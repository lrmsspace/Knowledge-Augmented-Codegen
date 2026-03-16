// Source: https://leetcode.com/problems/escape-the-spreading-fire/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array grid of size m x n which represents a field. Each cell has one of three values:
//
//
// 	0 represents grass,
// 	1 represents fire,
// 	2 represents a wall that you and fire cannot pass through.
//
//
// You are situated in the top-left cell, (0, 0), and you want to travel to the safehouse at the bottom-right cell, (m - 1, n - 1). Every minute, you may move to an adjacent grass cell. After your move, every fire cell will spread to all adjacent cells that are not walls.
//
// Return the maximum number of minutes that you can stay in your initial position before moving while still safely reaching the safehouse. If this is impossible, return -1. If you can always reach the safehouse regardless of the minutes stayed, return 109.
//
// Note that even if the fire spreads to the safehouse immediately after you have reached it, it will be counted as safely reaching the safehouse.
//
// A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
//
// Example:
// Input: grid = [[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]
// Output: 3
// Explanation: The figure above shows the scenario where you stay in the initial position for 3 minutes.
// You will still be able to safely reach the safehouse.
// Staying for more than 3 minutes will not allow you to safely reach the safehouse.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 300
// 	4 <= m * n <= 2 * 104
// 	grid[i][j] is either 0, 1, or 2.
// 	grid[0][0] == grid[m - 1][n - 1] == 0
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - Maximum flow - Ford-Fulkerson and Edmonds-Karp (graph, array, bfs)
//   • When to use: When needing to find the maximum possible flow from a source to a sink in a flow network. It is particularly useful for problems involving resource allocation, transportation, or matching.
//   • Idea: Ford-Fulkerson finds maximum flow by repeatedly augmenting paths in a residual graph. Edmonds-Karp uses BFS for shortest augmenting paths, ensuring O(VE^2) time complexity and termination.
//   • Invariants: The flow through any edge never exceeds its capacity.; For every vertex (except source and sink), total incoming flow equals total outgoing flow (flow conservation).
//   • Tips: Always construct a residual graph to represent remaining capacities and backward flow.; BFS ensures finding the shortest augmenting path, leading to the O(VE^2) complexity.
//   • Pitfalls: Incorrectly updating residual capacities for backward edges can lead to wrong results.; Using DFS for Ford-Fulkerson can lead to poor performance or non-termination with irrational capacities.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maximumMinutes(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> fireTime(m, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;

        // Initialize fire positions
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    fireTime[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        // Directions for moving up, down, left, right
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // Multi-source BFS to calculate fire spread time
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (auto& dir : directions) {
                int newX = x + dir.first;
                int newY = y + dir.second;
                if (newX >= 0 && newX < m && newY >= 0 && newY < n &&
                    grid[newX][newY] != 2 && fireTime[newX][newY] == INT_MAX) {
                    fireTime[newX][newY] = fireTime[x][y] + 1;
                    q.push({newX, newY});
                }
            }
        }

        // Binary search for maximum wait time
        int left = -1, right = 1e9;
        auto canReachSafehouse = [&](int waitTime) {
            if (waitTime >= fireTime[0][0]) return false;
            vector<vector<int>> personTime(m, vector<int>(n, INT_MAX));
            queue<pair<int, int>> pq;
            personTime[0][0] = waitTime;
            pq.push({0, 0});

            while (!pq.empty()) {
                auto [x, y] = pq.front();
                pq.pop();
                for (auto& dir : directions) {
                    int newX = x + dir.first;
                    int newY = y + dir.second;
                    if (newX >= 0 && newX < m && newY >= 0 && newY < n &&
                        grid[newX][newY] != 2) {
                        int arrivalTime = personTime[x][y] + 1;
                        if (arrivalTime < fireTime[newX][newY] &&
                            arrivalTime < personTime[newX][newY]) {
                            personTime[newX][newY] = arrivalTime;
                            pq.push({newX, newY});
                        }
                    }
                }
            }
            return personTime[m - 1][n - 1] != INT_MAX;
        };
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (canReachSafehouse(mid)) {
                left = mid;
            } else {
                right = mid - 1;
            }
        }
        return left;
    }
};
