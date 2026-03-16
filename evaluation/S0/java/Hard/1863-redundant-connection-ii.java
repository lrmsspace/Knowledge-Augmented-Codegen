// Source: https://leetcode.com/problems/redundant-connection-ii/   |   Difficulty: Hard
//
// Problem Description:
// In this problem, a rooted tree is a directed graph such that, there is exactly one node (the root) for which all other nodes are descendants of this node, plus every node has exactly one parent, except for the root node which has no parents.
//
// The given input is a directed graph that started as a rooted tree with n nodes (with distinct values from 1 to n), with one additional directed edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed.
//
// The resulting graph is given as a 2D-array of edges. Each element of edges is a pair [ui, vi] that represents a directed edge connecting nodes ui and vi, where ui is a parent of child vi.
//
// Return an edge that can be removed so that the resulting graph is a rooted tree of n nodes. If there are multiple answers, return the answer that occurs last in the given 2D-array.
//
// Example:
// Input: edges = [[1,2],[1,3],[2,3]]
// Output: [2,3]
//
// Constraints:
// n == edges.length
// 	3 <= n <= 1000
// 	edges[i].length == 2
// 	1 <= ui, vi <= n
// 	ui != vi
//

class Solution {
    public int[] findRedundantDirectedConnection(int[][] edges) {
        int n = edges.length;
        int[] parent = new int[n + 1];
        int[] candA = null;
        int[] candB = null;

        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            if (parent[v] == 0) {
                parent[v] = u;
            } else {
                candA = new int[] {parent[v], v};
                candB = new int[] {u, v};
                edge[1] = 0; // invalidate this edge
            }
        }

        UnionFind uf = new UnionFind(n + 1);
        for (int[] edge : edges) {
            int u = edge[0], v = edge[1];
            if (v == 0) continue; // skip invalidated edge
            if (!uf.union(u, v)) {
                if (candA == null) {
                    return edge;
                } else {
                    return candA;
                }
            }
        }

        return candB;           
    }
}
