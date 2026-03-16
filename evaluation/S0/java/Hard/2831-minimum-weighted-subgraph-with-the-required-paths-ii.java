// Source: https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected weighted tree with n nodes, numbered from 0 to n - 1. It is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi.​
//
// Additionally, you are given a 2D integer array queries, where queries[j] = [src1j, src2j, destj].
//
// Return an array answer of length equal to queries.length, where answer[j] is the minimum total weight of a subtree such that it is possible to reach destj from both src1j and src2j using edges in this subtree.
//
// A subtree here is any connected subset of nodes and edges of the original tree forming a valid tree.
//
// Example:
// Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], queries = [[2,3,4],[0,2,5]]
//
// Output: [12,11]
//
// Explanation:
//
// The blue edges represent one of the subtrees that yield the optimal answer.
//
//
//
//
// 	
// 	answer[0]: The total weight of the selected subtree that ensures a path from src1 = 2 and src2 = 3 to dest = 4 is 3 + 5 + 4 = 12.
// 	
// 	
// 	answer[1]: The total weight of the selected subtree that ensures a path from src1 = 0 and src2 = 2 to dest = 5 is 2 + 3 + 6 = 11.
//
// Constraints:
// 3 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= ui, vi < n
// 	1 <= wi <= 104
// 	1 <= queries.length <= 105
// 	queries[j].length == 3
// 	0 <= src1j, src2j, destj < n
// 	src1j, src2j, and destj are pairwise distinct.
// 	The input is generated such that edges represents a valid tree.
//

class Solution {
    public int[] minimumWeight(int[][] edges, int[][] queries) {
        int n = edges.length + 1;
        List<int[]>[] graph = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            graph[i] = new ArrayList<>();
        }
        for (int[] edge : edges) {
            graph[edge[0]].add(new int[]{edge[1], edge[2]});
            graph[edge[1]].add(new int[]{edge[0], edge[2]});
        }

        int LOG = 17;
        int[][] parent = new int[n][LOG];
        long[][] dist = new long[n][LOG];
        int[] depth = new int[n];

        dfs(0, -1, 0, graph, parent, dist, depth);

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {
                if (parent[i][j - 1] != -1) {
                    parent[i][j] = parent[parent[i][j - 1]][j - 1];
                    dist[i][j] = dist[i][j - 1] + dist[parent[i][j - 1]][j - 1];
                } else {
                    parent[i][j] = -1;
                }
            }
        }

        int qLen = queries.length;
        int[] result = new int[qLen];
        for (int i = 0; i < qLen; i++) {
            int src1 = queries[i][0];
            int src2 = queries[i][1];
            int dest = queries[i][2];

            long totalDist = getDistance(src1, dest, parent, dist, depth)
                            + getDistance(src2, dest, parent, dist, depth);
            result[i] = (int) totalDist;
        }

        return result;          
    }
}
