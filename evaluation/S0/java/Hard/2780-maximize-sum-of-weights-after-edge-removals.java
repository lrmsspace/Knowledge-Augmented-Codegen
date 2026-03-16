// Source: https://leetcode.com/problems/maximize-sum-of-weights-after-edge-removals/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi in the tree.
//
// Your task is to remove zero or more edges such that:
//
//
// 	Each node has an edge with at most k other nodes, where k is given.
// 	The sum of the weights of the remaining edges is maximized.
//
//
// Return the maximum possible sum of weights for the remaining edges after making the necessary removals.
//
// Example:
// Input: edges = [[0,1,4],[0,2,2],[2,3,12],[2,4,6]], k = 2
//
// Output: 22
//
// Explanation:
//
//
//
//
// 	Node 2 has edges with 3 other nodes. We remove the edge [0, 2, 2], ensuring that no node has edges with more than k = 2 nodes.
// 	The sum of weights is 22, and we can't achieve a greater sum. Thus, the answer is 22.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= k <= n - 1
// 	edges.length == n - 1
// 	edges[i].length == 3
// 	0 <= edges[i][0] <= n - 1
// 	0 <= edges[i][1] <= n - 1
// 	1 <= edges[i][2] <= 106
// 	The input is generated such that edges form a valid tree.
//

class Solution {
    public long maximizeSumOfWeights(int[][] edges, int k) {
        int n = edges.length + 1;
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(new int[]{edge[1], edge[2]});
            graph.get(edge[1]).add(new int[]{edge[0], edge[2]});
        }

        long result = 0;
        boolean[] visited = new boolean[n];
        PriorityQueue<Long> pq = new PriorityQueue<>(Collections.reverseOrder());
        pq.offer(0L); // Start with root node contribution

        while (!pq.isEmpty()) {
            long currWeight = pq.poll();
            result += currWeight;

            // Process children of the current node
            List<Long> childWeights = new ArrayList<>();
            for (int i = 0; i < n; i++) {
                if (!visited[i]) {
                    visited[i] = true;
                    for (int[] neighbor : graph.get(i)) {
                        if (!visited[neighbor[0]]) {
                            childWeights.add((long) neighbor[1]);
                        }
                    }
                }
            }

            // Sort child weights in descending order
            Collections.sort(childWeights, Collections.reverseOrder());

            // Add top k child weights to the priority queue
            for (int i = 0; i < Math.min(k, childWeights.size()); i++) {
                pq.offer(childWeights.get(i));
            }
        }

        return result;          
    }
}
