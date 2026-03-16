// Source: https://leetcode.com/problems/construct-2d-grid-matching-graph-layout/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array edges representing an undirected graph having n nodes, where edges[i] = [ui, vi] denotes an edge between nodes ui and vi.
//
// Construct a 2D grid that satisfies these conditions:
//
//
// 	The grid contains all nodes from 0 to n - 1 in its cells, with each node appearing exactly once.
// 	Two nodes should be in adjacent grid cells (horizontally or vertically) if and only if there is an edge between them in edges.
//
//
// It is guaranteed that edges can form a 2D grid that satisfies the conditions.
//
// Return a 2D integer array satisfying the conditions above. If there are multiple solutions, return any of them.
//
// Example:
// Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]]
//
// Output: [[3,1],[2,0]]
//
// Explanation:
//
// Constraints:
// 2 <= n <= 5 * 104
// 	1 <= edges.length <= 105
// 	edges[i] = [ui, vi]
// 	0 <= ui < vi < n
// 	All the edges are distinct.
// 	The input is generated such that edges can form a 2D grid that satisfies the conditions.
//
// Helpful references (internal KB):
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
// - Depth First Search (graph, dfs, topo)
//   • When to use: Use DFS to explore all reachable vertices from a starting point, find paths, detect cycles, or perform topological sorting on directed acyclic graphs.
//   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically runs in O(V + E) time for graphs represented with adjacency lists, where V is the number of vertices and E is the number of edges.
//   • Invariants: Every node is visited at most once.; The `visited` set accurately reflects nodes currently in the recursion stack or fully explored.
//   • Tips: Always use a visited set to avoid infinite loops in cyclic graphs.; For topological sort, add nodes to a list after visiting all their neighbors.
//   • Pitfalls: Risk of stack overflow for very deep graphs or trees.; Failing to mark nodes as visited before recursive calls can lead to re-processing.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        // Build adjacency list
        vector<vector<int>> graph(n);
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // BFS to assign coordinates
        vector<vector<int>> coords(n, vector<int>(2, -1));
        queue<int> q;
        q.push(0);
        coords[0] = {0, 0};

        vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            int x = coords[node][0];
            int y = coords[node][1];

            for (int neighbor : graph[node]) {
                if (coords[neighbor][0] == -1) { // Not visited
                    // Find an available direction
                    for (const auto& dir : directions) {
                        int newX = x + dir[0];
                        int newY = y + dir[1];
                        bool occupied = false;
                        for (const auto& c : coords) {
                            if (c[0] == newX && c[1] == newY) {
                                occupied = true;
                                break;
                            }
                        }
                        if (!occupied) {
                            coords[neighbor] = {newX, newY};
                            q.push(neighbor);
                            break;
                        }
                    }
                }
            }
        }

        // Find grid bounds
        int minX = INT32_MAX, maxX = INT32_MIN, minY = INT32_MAX, maxY = INT32_MIN;
        for (const auto& c : coords) {
            minX = min(minX, c[0]);
            maxX = max(maxX, c[0]);
            minY = min(minY, c[1]);
            maxY = max(maxY, c[1]);
        }

        int rows = maxX - minX + 1;
        int cols = maxY - minY + 1;

        // Construct the grid
        vector<vector<int>> grid(rows, vector<int>(cols, -1));
        for (int i = 0; i < n; ++i) {
            int x = coords[i][0] - minX;
            int y = coords[i][1] - minY;    
            grid[x][y] = i;
        }
        return grid;
    }
};
