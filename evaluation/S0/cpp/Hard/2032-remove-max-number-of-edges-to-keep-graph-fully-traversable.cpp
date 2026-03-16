// Source: https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/   |   Difficulty: Hard
//
// Problem Description:
// Alice and Bob have an undirected graph of n nodes and three types of edges:
//
//
// 	Type 1: Can be traversed by Alice only.
// 	Type 2: Can be traversed by Bob only.
// 	Type 3: Can be traversed by both Alice and Bob.
//
//
// Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi, find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob. The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.
//
// Return the maximum number of edges you can remove, or return -1 if Alice and Bob cannot fully traverse the graph.
//
// Example:
// Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
// Output: 2
// Explanation: If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= edges.length <= min(105, 3 * n * (n - 1) / 2)
// 	edges[i].length == 3
// 	1 <= typei <= 3
// 	1 <= ui < vi <= n
// 	All tuples (typei, ui, vi) are distinct.
//

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        vector<int> parentA(n + 1), parentB(n + 1);
        for (int i = 1; i <= n; i++) {
            parentA[i] = i;
            parentB[i] = i;
        }
        
        function<int(vector<int>&, int)> find = [&](vector<int>& parent, int u) {
            if (parent[u] != u) {
                parent[u] = find(parent, parent[u]);
            }
            return parent[u];
        };
        
        int usedEdges = 0;
        
        // First, use type 3 edges
        for (const auto& edge : edges) {
            if (edge[0] == 3) {
                int u = edge[1], v = edge[2];
                int puA = find(parentA, u), pvA = find(parentA, v);
                if (puA != pvA) {
                    parentA[puA] = pvA;
                    int puB = find(parentB, u), pvB = find(parentB, v);
                    parentB[puB] = pvB;
                    usedEdges++;
                }
            }
        }
        
        // Then, use type 1 edges for Alice
        for (const auto& edge : edges) {
            if (edge[0] == 1) {
                int u = edge[1], v = edge[2];
                int puA = find(parentA, u), pvA = find(parentA, v);
                if (puA != pvA) {
                    parentA[puA] = pvA;
                    usedEdges++;
                }
            }
        }
        
        // Finally, use type 2 edges for Bob
        for (const auto& edge : edges) {
            if (edge[0] == 2) {
                int u = edge[1], v = edge[2];
                int puB = find(parentB, u), pvB = find(parentB, v);
                if (puB != pvB) {
                    parentB[puB] = pvB;
                    usedEdges++;
                }
            }
        }
        
        // Check if both Alice and Bob can traverse the whole graph
        int rootA = find(parentA, 1);
        int rootB = find(parentB, 1);
        for (int i = 2; i <= n; i++) {
            if (find(parentA, i) != rootA || find(parentB, i) != rootB) {
                return -1;
            }
        }
        return edges.size() - usedEdges;    
    }
};
