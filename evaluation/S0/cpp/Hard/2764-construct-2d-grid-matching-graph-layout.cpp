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

class Solution {
public:
    vector<vector<int>> constructGridLayout(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        vector<int> degree(n, 0);
        
        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1];
            graph[u].push_back(v);
            graph[v].push_back(u);
            degree[u]++;
            degree[v]++;
        }
        
        int rows = 0, cols = 0;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 2) {
                rows++;
            } else if (degree[i] == 3) {
                cols++;
            }
        }
        rows = rows / cols + 1;
        
        vector<vector<int>> grid(rows, vector<int>(cols, -1));
        vector<bool> visited(n, false);
        
        // Find a corner node (degree 2)
        int start = -1;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 2) {
                start = i;
                break;
            }
        }
        
        // BFS to fill the grid
        queue<pair<int, int>> q;
        q.push({start, 0});
        visited[start] = true;
        grid[0][0] = start;
        
        int directions[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        
        while (!q.empty()) {
            auto [node, idx] = q.front();
            q.pop();
            
            int r = idx / cols;
            int c = idx % cols;
            
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    // Find next position
                    for (auto& dir : directions) {
                        int nr = r + dir[0];
                        int nc = c + dir[1];
                        if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == -1) {
                            grid[nr][nc] = neighbor;
                            q.push({neighbor, nr * cols + nc});
                            break;
                        }
                    }
                }
            }
        }
        
        return grid;            
    }
};
