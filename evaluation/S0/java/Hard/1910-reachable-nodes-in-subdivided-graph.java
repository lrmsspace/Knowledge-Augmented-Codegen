// Source: https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph (the "original graph") with n nodes labeled from 0 to n - 1. You decide to subdivide each edge in the graph into a chain of nodes, with the number of new nodes varying between each edge.
//
// The graph is given as a 2D array of edges where edges[i] = [ui, vi, cnti] indicates that there is an edge between nodes ui and vi in the original graph, and cnti is the total number of new nodes that you will subdivide the edge into. Note that cnti == 0 means you will not subdivide the edge.
//
// To subdivide the edge [ui, vi], replace it with (cnti + 1) new edges and cnti new nodes. The new nodes are x1, x2, ..., xcnti, and the new edges are [ui, x1], [x1, x2], [x2, x3], ..., [xcnti-1, xcnti], [xcnti, vi].
//
// In this new graph, you want to know how many nodes are reachable from the node 0, where a node is reachable if the distance is maxMoves or less.
//
// Given the original graph and maxMoves, return the number of nodes that are reachable from node 0 in the new graph.
//
// Example:
// Input: edges = [[0,1,10],[0,2,1],[1,2,2]], maxMoves = 6, n = 3
// Output: 13
// Explanation: The edge subdivisions are shown in the image above.
// The nodes that are reachable are highlighted in yellow.
//
// Constraints:
// 0 <= edges.length <= min(n * (n - 1) / 2, 104)
// 	edges[i].length == 3
// 	0 <= ui < vi < n
// 	There are no multiple edges in the graph.
// 	0 <= cnti <= 104
// 	0 <= maxMoves <= 109
// 	1 <= n <= 3000
//

class Solution {
    public int reachableNodes(int[][] edges, int maxMoves, int n) {
        Map<Integer, List<int[]>> graph = new HashMap<>();
        for (int[] edge : edges) {
            graph.computeIfAbsent(edge[0], k -> new ArrayList<>()).add(new int[]{edge[1], edge[2]});
            graph.computeIfAbsent(edge[1], k -> new ArrayList<>()).add(new int[]{edge[0], edge[2]});
        }

        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> b[0] - a[0]);
        pq.offer(new int[]{maxMoves, 0});

        Map<Integer, Integer> dist = new HashMap<>();
        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int movesLeft = curr[0];
            int node = curr[1];

            if (dist.containsKey(node)) {
                continue;
            }
            dist.put(node, movesLeft);

            if (!graph.containsKey(node)) {
                continue;
            }

            for (int[] neighbor : graph.get(node)) {
                int nextNode = neighbor[0];
                int weight = neighbor[1] + 1;

                if (!dist.containsKey(nextNode) && movesLeft >= weight) {
                    pq.offer(new int[]{movesLeft - weight, nextNode});
                }
            }
        }

        int result = dist.size();
        for (int[] edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cnt = edge[2];

            int uReach = dist.getOrDefault(u, 0);
            int vReach = dist.getOrDefault(v, 0);

            result += Math.min(cnt, uReach + vReach);
        }

        return result;          
    }
}
