// Source: https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected graph consisting of n nodes numbered from 1 to n. You are given the integer n and a 2D array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi. The graph can be disconnected.
//
// You can add at most two additional edges (possibly none) to this graph so that there are no repeated edges and no self-loops.
//
// Return true if it is possible to make the degree of each node in the graph even, otherwise return false.
//
// The degree of a node is the number of edges connected to it.
//
// Example:
// Input: n = 5, edges = [[1,2],[2,3],[3,4],[4,2],[1,4],[2,5]]
// Output: true
// Explanation: The above diagram shows a valid way of adding an edge.
// Every node in the resulting graph is connected to an even number of edges.
//
// Constraints:
// 3 <= n <= 105
// 	2 <= edges.length <= 105
// 	edges[i].length == 2
// 	1 <= ai, bi <= n
// 	ai != bi
// 	There are no repeated edges.
//

class Solution {
public:
    bool isPossible(int n, vector<vector<int>>& edges) {
        vector<int> degree(n + 1, 0);
        for (const auto& edge : edges) {
            degree[edge[0]]++;
            degree[edge[1]]++;
        }
        
        vector<int> oddNodes;
        for (int i = 1; i <= n; i++) {
            if (degree[i] % 2 != 0) {
                oddNodes.push_back(i);
            }
        }
        
        int oddCount = oddNodes.size();
        if (oddCount == 0) {
            return true;
        } else if (oddCount == 2) {
            int u = oddNodes[0];
            int v = oddNodes[1];
            // Check if we can connect u and v directly
            bool canConnectDirectly = true;
            for (const auto& edge : edges) {
                if ((edge[0] == u && edge[1] == v) || (edge[0] == v && edge[1] == u)) {
                    canConnectDirectly = false;
                    break;
                }
            }
            if (canConnectDirectly) {
                return true;
            }
            // Try to find an intermediate node
            for (int i = 1; i <= n; i++) {
                if (i != u && i != v) {
                    bool canConnectU = true, canConnectV = true;
                    for (const auto& edge : edges) {
                        if ((edge[0] == u && edge[1] == i) || (edge[0] == i && edge[1] == u)) {
                            canConnectU = false;
                        }
                        if ((edge[0] == v && edge[1] == i) || (edge[0] == i && edge[1] == v)) {
                            canConnectV = false;
                        }
                    }
                    if (canConnectU && canConnectV) {
                        return true;
                    }
                }
            }
            return false;
        } else if (oddCount == 4) {
            // Check all pairings
            for (int i = 0; i < 4; i++) {
                for (int j = i + 1; j < 4; j++) {
                    int u1 = oddNodes[i];
                    int v1 = oddNodes[j];
                    bool canConnectFirstPair = true;          
                    for (const auto& edge : edges) {
                        if ((edge[0] == u1 && edge[1] == v1) || (edge[0] == v1 && edge[1] == u1)) {
                            canConnectFirstPair = false;
                            break;
                        }
                    }
                    for (int k = 0; k < 4; k++) {
                        if (k == i || k == j) continue;
                        for (int l = k + 1; l < 4; l++) {
                            if (l == i || l == j) continue;
                            int u2 = oddNodes[k];
                            int v2 = oddNodes[l];
                            bool canConnectSecondPair = true;
                            for (const auto& edge : edges) {
                                if ((edge[0] == u2 && edge[1] == v2) || (edge[0] == v2 && edge[1] == u2)) {
                                    canConnectSecondPair = false;
                                    break;
                                }
                            }
                            if (canConnectFirstPair && canConnectSecondPair) {
                                return true;
                            }
                        }
                    }
                      
            return false;
        } else {
            return false;
        }
        
    }
};
