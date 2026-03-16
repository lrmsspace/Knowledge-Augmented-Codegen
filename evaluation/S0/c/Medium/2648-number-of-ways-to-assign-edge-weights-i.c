// Source: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-i/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.
//
// Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.
//
// The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.
//
// Select any one node x at the maximum depth. Return the number of ways to assign edge weights in the path from node 1 to x such that its total cost is odd.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Note: Ignore all edges not in the path from node 1 to x.
//
// Example:
// Input: edges = [[1,2]]
//
// Output: 1
//
// Explanation:
//
//
// 	The path from Node 1 to Node 2 consists of one edge (1 → 2).
// 	Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi]
// 	1 <= ui, vi <= n
// 	edges represents a valid tree.
//

int assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize) {
    const int MOD = 1e9 + 7;
    // In a tree with n nodes, there are always n-1 edges.
    // To maximize the depth from the root (node 1), we can consider a linear tree (a straight path).
    // In such a case, the maximum depth is n-1.
    // To have an odd total cost from node 1 to the deepest node, we need an odd number of edges with weight 1.
    // The number of ways to assign weights such that the total cost is odd is equal to the number of ways to choose an odd number of edges to assign weight 1.
    // For a path with n-1 edges, there are 2^(n-2) ways to assign weights such that the total cost is odd.
    
    long long n = edgesSize + 1; // Number of nodes
    long long result = 1;
    
    // Calculate 2^(n-2) % MOD
    for (long long i = 0; i < n - 2; ++i) {
        result = (result * 2) % MOD;
    }
    
    return (int)result;     
}
