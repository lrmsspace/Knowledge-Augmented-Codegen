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

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n - 1) {
            return -1; // Not enough cables to connect all computers
        }

        vector<int> parent(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }

        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };

        for (const auto& conn : connections) {
            int rootA = find(conn[0]);
            int rootB = find(conn[1]);
            if (rootA != rootB) {
                parent[rootA] = rootB; // Union
            }
        }

        unordered_set<int> uniqueRoots;
        for (int i = 0; i < n; ++i) {
            uniqueRoots.insert(find(i));
        }

        return uniqueRoots.size() - 1; // Number of operations needed           
    }
};
