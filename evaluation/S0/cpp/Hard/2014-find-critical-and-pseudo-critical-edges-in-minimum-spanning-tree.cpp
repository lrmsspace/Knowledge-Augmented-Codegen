// Source: https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/   |   Difficulty: Hard
//
// Problem Description:
// Given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional and weighted edge between nodes ai and bi. A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cycles and with the minimum possible total edge weight.
//
// Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST). An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge. On the other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.
//
// Note that you can return the indices of the edges in any order.
//
// Example:
// Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
// Output: [[0,1],[2,3,4,5]]
// Explanation: The figure above describes the graph.
// The following figure shows all the possible MSTs:
//
// Notice that the two edges 0 and 1 appear in all MSTs, therefore they are critical edges, so we return them in the first list of the output.
// The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered pseudo-critical edges. We add them to the second list of the output.
//
// Constraints:
// 2 <= n <= 100
// 	1 <= edges.length <= min(200, n * (n - 1) / 2)
// 	edges[i].length == 3
// 	0 <= ai < bi < n
// 	1 <= weighti <= 1000
// 	All pairs (ai, bi) are distinct.
//

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        // Kruskal's algorithm with Union-Find
        function<int(int, vector<int>&)> find = [&](int x, vector<int>& parent) {
            if (parent[x] != x) {
                parent[x] = find(parent[x], parent);
            }
            return parent[x];
        };
        
        function<int(int, int, vector<int>&, vector<int>&)> unionSets = [&](int x, int y, vector<int>& parent, vector<int>& rank) {
            int rootX = find(x, parent);
            int rootY = find(y, parent);
            if (rootX == rootY) return 0;
            
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
            return 1;
        };
        
        // Prepare edges with original indices
        int m = edges.size();
        vector<vector<int>> indexedEdges(m);
        for (int i = 0; i < m; i++) {
            indexedEdges[i] = {edges[i][0], edges[i][1], edges[i][2], i};
        }
        
        // Sort edges by weight
        sort(indexedEdges.begin(), indexedEdges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });
        
        // Function to compute MST weight with optional edge inclusion/exclusion
        auto computeMST = [&](int n, vector<vector<int>>& edges, int excludeEdge, int includeEdge) {
            vector<int> parent(n), rank(n, 0);
            for (int i = 0; i < n; i++) parent[i] = i;
            
            int totalWeight = 0;
            int edgesUsed = 0;
            
            // Include the specified edge first
            if (includeEdge != -1) {
                totalWeight += edges[includeEdge][2];
                unionSets(edges[includeEdge][0], edges[includeEdge][1], parent, rank);
                edgesUsed++;
            }
            
            for (int i = 0; i < edges.size(); i++) {
                if (i == excludeEdge) continue;
                
                if (unionSets(edges[i][0], edges[i][1], parent, rank)) {
                    totalWeight += edges[i][2];
                    edgesUsed++;
                }
            }
            return edgesUsed == n - 1 ? totalWeight : INT_MAX;
        };
        
        int originalMSTWeight = computeMST(n, indexedEdges, -1, -1);
        vector<int> critical, pseudoCritical;
        
        for (int i = 0; i < m; i++) {
            // Check if edge is critical
            if (computeMST(n, indexedEdges, i, -1) > originalMSTWeight) {
                critical.push_back(indexedEdges[i][3]);
            } else if (computeMST(n, indexedEdges, -1, i) == originalMSTWeight) {
                pseudoCritical.push_back(indexedEdges[i][3]);
            }
        }
        
        return {critical, pseudoCritical};
    }
};