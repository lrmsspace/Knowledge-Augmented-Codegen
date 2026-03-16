// Source: https://leetcode.com/problems/count-unreachable-pairs-of-nodes-in-an-undirected-graph/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. There is an undirected graph with n nodes, numbered from 0 to n - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// Return the number of pairs of different nodes that are unreachable from each other.
//
// Example:
// Input: n = 3, edges = [[0,1],[0,2],[1,2]]
// Output: 0
// Explanation: There are no pairs of nodes that are unreachable from each other. Therefore, we return 0.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= edges.length <= 2 * 105
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	There are no repeated edges.
//

long long countPairs(int n, int** edges, int edgesSize, int* edgesColSize) {
    // Union-Find (Disjoint Set Union) Data Structure
    int* parent = (int*)malloc(n * sizeof(int));
    int* size = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    // Find function with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union function by size
    void unionSets(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);
        if (rootA != rootB) {
            if (size[rootA] < size[rootB]) {
                parent[rootA] = rootB;
                size[rootB] += size[rootA];
            } else {
                parent[rootB] = rootA;
                size[rootA] += size[rootB];
            }
        }
    }

    // Process each edge to union the nodes
    for (int i = 0; i < edgesSize; i++) {
        unionSets(edges[i][0], edges[i][1]);
    }

    // Calculate the number of unreachable pairs
    long long totalPairs = (long long)n * (n - 1) / 2;
    for (int i = 0; i < n; i++) {
        if (parent[i] == i) { // If it's a root node
            long long componentSize = size[i];
            totalPairs -= (componentSize * (componentSize - 1)) / 2;
        }
    }

    free(parent);
    free(size);
    return totalPairs;      
}
