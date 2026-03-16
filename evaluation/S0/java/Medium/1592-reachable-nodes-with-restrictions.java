// Source: https://leetcode.com/problems/reachable-nodes-with-restrictions/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 0 to n - 1 and n - 1 edges.
//
// You are given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree. You are also given an integer array restricted which represents restricted nodes.
//
// Return the maximum number of nodes you can reach from node 0 without visiting a restricted node.
//
// Note that node 0 will not be a restricted node.
//
// Example:
// Input: n = 7, edges = [[0,1],[1,2],[3,1],[4,0],[0,5],[5,6]], restricted = [4,5]
// Output: 4
// Explanation: The diagram above shows the tree.
// We have that [0,1,2,3] are the only nodes that can be reached from node 0 without visiting a restricted node.
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= ai, bi < n
// 	ai != bi
// 	edges represents a valid tree.
// 	1 <= restricted.length < n
// 	1 <= restricted[i] < n
// 	All the values of restricted are unique.
//

class Solution {
    public int reachableNodes(int n, int[][] edges, int[] restricted) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }

        Set<Integer> restrictedSet = new HashSet<>();
        for (int r : restricted) {
            restrictedSet.add(r);
        }

        boolean[] visited = new boolean[n];
        return dfs(0, graph, restrictedSet, visited);           
    }
}
