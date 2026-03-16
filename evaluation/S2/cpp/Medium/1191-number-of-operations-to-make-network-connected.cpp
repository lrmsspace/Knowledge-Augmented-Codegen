// Source: https://leetcode.com/problems/number-of-operations-to-make-network-connected/   |   Difficulty: Medium
//
// Problem Description:
// There are n computers numbered from 0 to n - 1 connected by ethernet cables connections forming a network where connections[i] = [ai, bi] represents a connection between computers ai and bi. Any computer can reach any other computer directly or indirectly through the network.
//
// You are given an initial computer network connections. You can extract certain cables between two directly connected computers, and place them between any pair of disconnected computers to make them directly connected.
//
// Return the minimum number of times you need to do this in order to make all the computers connected. If it is not possible, return -1.
//
// Example:
// Input: n = 4, connections = [[0,1],[0,2],[1,2]]
// Output: 1
// Explanation: Remove cable between computer 1 and 2 and place between computers 1 and 3.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= connections.length <= min(n * (n - 1) / 2, 105)
// 	connections[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	There are no repeated connections.
// 	No two computers are connected by more than one cable.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1) {
            return -1; // Not enough cables to connect all computers
        }

        vector<vector<int>> graph(n);
        for (const auto& conn : connections) {
            graph[conn[0]].push_back(conn[1]);
            graph[conn[1]].push_back(conn[0]);
        }

        vector<bool> visited(n, false);
        int components = 0;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                ++components;
                dfs(graph, visited, i);
            }
        }

        return components - 1; // Minimum operations needed is number of components - 1         
    }
};
