// Source: https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected weighted connected graph. You are given a positive integer n which denotes that the graph has n nodes labeled from 1 to n, and an array edges where each edges[i] = [ui, vi, weighti] denotes that there is an edge between nodes ui and vi with weight equal to weighti.
//
// A path from node start to node end is a sequence of nodes [z0, z1, z2, ..., zk] such that z0 = start and zk = end and there is an edge between zi and zi+1 where 0 <= i <= k-1.
//
// The distance of a path is the sum of the weights on the edges of the path. Let distanceToLastNode(x) denote the shortest distance of a path between node n and node x. A restricted path is a path that also satisfies that distanceToLastNode(zi) > distanceToLastNode(zi+1) where 0 <= i <= k-1.
//
// Return the number of restricted paths from node 1 to node n. Since that number may be too large, return it modulo 109 + 7.
//
// Example:
// Input: n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
// Output: 3
// Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The three restricted paths are:
// 1) 1 --> 2 --> 5
// 2) 1 --> 2 --> 3 --> 5
// 3) 1 --> 3 --> 5
//
// Constraints:
// 1 <= n <= 2 * 104
// 	n - 1 <= edges.length <= 4 * 104
// 	edges[i].length == 3
// 	1 <= ui, vi <= n
// 	ui != vi
// 	1 <= weighti <= 105
// 	There is at most one edge between any two nodes.
// 	There is at least one path between any two nodes.
//

class Solution {
    public int countRestrictedPaths(int n, int[][] edges) {
        final int MOD = 1_000_000_007;

        // Build the graph as an adjacency list
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(new int[]{edge[1], edge[2]});
            graph.get(edge[1]).add(new int[]{edge[0], edge[2]});
        }

        // Dijkstra's algorithm to find shortest distances from node n
        int[] dist = new int[n + 1];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[n] = 0;
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[1]));
        pq.offer(new int[]{n, 0});

        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int node = curr[0];
            int currDist = curr[1];

            if (currDist > dist[node]) continue;

            for (int[] neighbor : graph.get(node)) {
                int nextNode = neighbor[0];
                int weight = neighbor[1];
                if (dist[nextNode] > currDist + weight) {
                    dist[nextNode] = currDist + weight;
                    pq.offer(new int[]{nextNode, dist[nextNode]});
                }
            }
        }

        // DFS with memoization to count restricted paths
        Integer[] memo = new Integer[n + 1];
        return dfs(1, n, graph, dist, memo, MOD);           
    }
}
