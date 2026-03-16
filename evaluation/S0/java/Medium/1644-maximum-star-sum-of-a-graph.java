// Source: https://leetcode.com/problems/maximum-star-sum-of-a-graph/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected graph consisting of n nodes numbered from 0 to n - 1. You are given a 0-indexed integer array vals of length n where vals[i] denotes the value of the ith node.
//
// You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
//
// A star graph is a subgraph of the given graph having a center node containing 0 or more neighbors. In other words, it is a subset of edges of the given graph such that there exists a common node for all edges.
//
// The image below shows star graphs with 3 and 4 neighbors respectively, centered at the blue node.
//
// The star sum is the sum of the values of all the nodes present in the star graph.
//
// Given an integer k, return the maximum star sum of a star graph containing at most k edges.
//
// Example:
// Input: vals = [1,2,3,4,10,-10,-20], edges = [[0,1],[1,2],[1,3],[3,4],[3,5],[3,6]], k = 2
// Output: 16
// Explanation: The above diagram represents the input graph.
// The star graph with the maximum star sum is denoted by blue. It is centered at 3 and includes its neighbors 1 and 4.
// It can be shown it is not possible to get a star graph with a sum greater than 16.
//
// Constraints:
// n == vals.length
// 	1 <= n <= 105
// 	-104 <= vals[i] <= 104
// 	0 <= edges.length <= min(n * (n - 1) / 2, 105)
// 	edges[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	0 <= k <= n - 1
//

class Solution {
    public int maxStarSum(int[] vals, int[][] edges, int k) {
        int n = vals.length;
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }

        int maxStarSum = Integer.MIN_VALUE;
        for (int i = 0; i < n; i++) {
            List<Integer> neighbors = graph.get(i);
            PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
            for (int neighbor : neighbors) {
                if (vals[neighbor] > 0) {
                    maxHeap.offer(vals[neighbor]);
                }
            }

            int currentStarSum = vals[i];
            int edgesUsed = 0;
            while (!maxHeap.isEmpty() && edgesUsed < k) {
                currentStarSum += maxHeap.poll();
                edgesUsed++;
            }
            maxStarSum = Math.max(maxStarSum, currentStarSum);
        }

        return maxStarSum;          
    }
}
