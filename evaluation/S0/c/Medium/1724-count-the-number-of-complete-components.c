// Source: https://leetcode.com/problems/count-the-number-of-complete-components/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. There is an undirected graph with n vertices, numbered from 0 to n - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting vertices ai and bi.
//
// Return the number of complete connected components of the graph.
//
// A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
//
// A connected component is said to be complete if there exists an edge between every pair of its vertices.
//
// Example:
// Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
// Output: 3
// Explanation: From the picture above, one can see that all of the components of this graph are complete.
//
// Constraints:
// 1 <= n <= 50
// 	0 <= edges.length <= n * (n - 1) / 2
// 	edges[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no repeated edges.
//

int countCompleteComponents(int n, int** edges, int edgesSize, int* edgesColSize) {
    int parent[n];
    int rank[n];
    int edge_count[n];
    int node_count[n];
    
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
        edge_count[i] = 0;
        node_count[i] = 1;
    }
    
    // Find function with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    // Union function with union by rank
    void union_sets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
                node_count[rootX] += node_count[rootY];
                edge_count[rootX] += edge_count[rootY] + 1;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
                node_count[rootY] += node_count[rootX];
                edge_count[rootY] += edge_count[rootX] + 1;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
                node_count[rootX] += node_count[rootY];
                edge_count[rootX] += edge_count[rootY] + 1;
            }
        } else {
            edge_count[rootX]++;
        }
    }
    
    // Process each edge
    for (int i = 0; i < edgesSize; i++) {
        union_sets(edges[i][0], edges[i][1]);
    }
    
    // Count complete components
    int complete_components = 0;
    for (int i = 0; i < n; i++) {
        if (parent[i] == i) { // Only consider root nodes
            int nodes = node_count[i];
            int edges_needed = nodes * (nodes - 1) / 2;
            if (edge_count[i] == edges_needed) {
                complete_components++;
            }
        }
    }
    
    return complete_components;     
}
