// Source: https://leetcode.com/problems/path-existence-queries-in-a-graph-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n representing the number of nodes in a graph, labeled from 0 to n - 1.
//
// You are also given an integer array nums of length n and an integer maxDiff.
//
// An undirected edge exists between nodes i and j if the absolute difference between nums[i] and nums[j] is at most maxDiff (i.e., |nums[i] - nums[j]| <= maxDiff).
//
// You are also given a 2D integer array queries. For each queries[i] = [ui, vi], find the minimum distance between nodes ui and vi. If no path exists between the two nodes, return -1 for that query.
//
// Return an array answer, where answer[i] is the result of the ith query.
//
// Note: The edges between the nodes are unweighted.
//
// Example:
// Input: n = 5, nums = [1,8,3,4,2], maxDiff = 3, queries = [[0,3],[2,4]]
//
// Output: [1,1]
//
// Explanation:
//
// The resulting graph is:
//
//
//
//
// 	
// 		
// 			Query
// 			Shortest Path
// 			Minimum Distance
// 		
// 		
// 			[0, 3]
// 			0 → 3
// 			1
// 		
// 		
// 			[2, 4]
// 			2 → 4
// 			1
// 		
// 	
//
//
// Thus, the output is [1, 1].
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	0 <= nums[i] <= 105
// 	0 <= maxDiff <= 105
// 	1 <= queries.length <= 105
// 	queries[i] == [ui, vi]
// 	0 <= ui, vi < n
//

class Solution {
    public int[] pathExistenceQueries(int n, int[] nums, int maxDiff, int[][] queries) {
        UnionFind uf = new UnionFind(n);
        TreeMap<Integer, List<Integer>> map = new TreeMap<>();
        for (int i = 0; i < n; i++) {
            map.computeIfAbsent(nums[i], k -> new ArrayList<>()).add(i);
        }

        for (int key : map.keySet()) {
            List<Integer> list1 = map.get(key);
            List<Integer> list2 = map.get(key - maxDiff);
            if (list2 != null) {
                for (int u : list1) {
                    for (int v : list2) {
                        uf.union(u, v);
                    }
                }
            }
            List<Integer> list3 = map.get(key + maxDiff);
            if (list3 != null) {
                for (int u : list1) {
                    for (int v : list3) {
                        uf.union(u, v);
                    }
                }
            }
        }

        int m = queries.length;
        int[] result = new int[m];
        for (int i = 0; i < m; i++) {
            int u = queries[i][0];
            int v = queries[i][1];
            result[i] = uf.find(u) == uf.find(v) ? 1 : -1;
        }
        return result;          
    }
}
