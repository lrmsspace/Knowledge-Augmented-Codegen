// Source: https://leetcode.com/problems/surrounded-regions/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix board containing letters 'X' and 'O', capture regions that are surrounded:
//
//
// 	Connect: A cell is connected to adjacent cells horizontally or vertically.
// 	Region: To form a region connect every 'O' cell.
// 	Surround: The region is surrounded with 'X' cells if you can connect the region with 'X' cells and none of the region cells are on the edge of the board.
//
//
// To capture a surrounded region, replace all 'O's with 'X's in-place within the original board. You do not need to return anything.
//
// Example:
// Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
//
// Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
//
// Explanation:
//
// In the above diagram, the bottom region is not captured because it is on the edge of the board and cannot be surrounded.
//
// Constraints:
// m == board.length
// 	n == board[i].length
// 	1 <= m, n <= 200
// 	board[i][j] is 'X' or 'O'.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Breadth-first search (graph, deque, array, 01-bfs)
//   • When to use: When finding the shortest path in a graph where edge weights are restricted to 0 or 1, or when minimizing operations where some operations are 'free' (cost 0) and others have a unit cost (cost 1).
//   • Idea: A graph traversal algorithm that finds the shortest path from a source to all reachable nodes in a graph where edge weights are either 0 or 1. It uses a deque to prioritize 0-cost edges, achieving an optimal O(V + E) time complexity.
//   • Invariants: Nodes are added to the front of the deque if the edge weight is 0, and to the back if 1.; The distance `dist[u]` for any node `u` in the deque is either `k` or `k+1` for some integer `k`.
//   • Tips: Use a deque: push 0-cost edges to the front, 1-cost edges to the back.; Mark nodes visited to avoid cycles and redundant processing.
//   • Pitfalls: Incorrectly handling visited states can lead to infinite loops or incorrect paths.; Forgetting to initialize distances properly before starting the traversal.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;
        int m = board.size(), n = board[0].size();
        queue<pair<int, int>> q;

        // Step 1: Mark 'O's on the borders and their connected 'O's as 'E'
        for (int i = 0; i < m; ++i) {
            for (int j : {0, n - 1}) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'E';
                    q.push({i, j});
                }
            }
        }
        for (int j = 0; j < n; ++j) {
            for (int i : {0, m - 1}) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'E';
                    q.push({i, j});
                }
            }
        }

        // Directions for BFS
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        // Step 2: BFS to mark all connected 'O's to 'E'
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (const auto& [dx, dy] : directions) {
                int nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && board[nx][ny] == 'O') {
                    board[nx][ny] = 'E';
                    q.push({nx, ny});
                }
            }
        }

        // Step 3: Flip remaining 'O's to 'X' and 'E's back to 'O'
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                } else if (board[i][j] == 'E') {
                    board[i][j] = 'O';
                }
            }
        }           
    }
};
