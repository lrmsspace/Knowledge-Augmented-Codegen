// Source: https://leetcode.com/problems/find-the-maximum-sum-of-node-values/   |   Difficulty: Hard
//
// Problem Description:
// There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 0-indexed 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree. You are also given a positive integer k, and a 0-indexed array of non-negative integers nums of length n, where nums[i] represents the value of the node numbered i.
//
// Alice wants the sum of values of tree nodes to be maximum, for which Alice can perform the following operation any number of times (including zero) on the tree:
//
//
// 	Choose any edge [u, v] connecting the nodes u and v, and update their values as follows:
//
// 	
// 		nums[u] = nums[u] XOR k
// 		nums[v] = nums[v] XOR k
// 	
// 	
//
//
// Return the maximum possible sum of the values Alice can achieve by performing the operation any number of times.
//
// Example:
// Input: nums = [1,2,1], k = 3, edges = [[0,1],[0,2]]
// Output: 6
// Explanation: Alice can achieve the maximum sum of 6 using a single operation:
// - Choose the edge [0,2]. nums[0] and nums[2] become: 1 XOR 3 = 2, and the array nums becomes: [1,2,1] -> [2,2,2].
// The total sum of values is 2 + 2 + 2 = 6.
// It can be shown that 6 is the maximum achievable sum of values.
//
// Constraints:
// 2 <= n == nums.length <= 2 * 104
// 	1 <= k <= 109
// 	0 <= nums[i] <= 109
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= edges[i][0], edges[i][1] <= n - 1
// 	The input is generated such that edges represent a valid tree.
//

class Solution {
    public long maximumValueSum(int[] nums, int k, int[][] edges) {
        int n = nums.length;
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }

        long[][] dp = new long[n][2];
        boolean[] visited = new boolean[n];
        dfs(0, graph, nums, k, dp, visited);

        return Math.max(dp[0][0], dp[0][1]);            
    }
}
