// Source: https://leetcode.com/problems/shortest-path-in-a-weighted-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an undirected, weighted tree rooted at node 1 with n nodes numbered from 1 to n. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an undirected edge from node ui to vi with weight wi.
//
// You are also given a 2D integer array queries of length q, where each queries[i] is either:
//
//
// 	[1, u, v, w'] – Update the weight of the edge between nodes u and v to w', where (u, v) is guaranteed to be an edge present in edges.
// 	[2, x] – Compute the shortest path distance from the root node 1 to node x.
//
//
// Return an integer array answer, where answer[i] is the shortest path distance from node 1 to x for the ith query of [2, x].
//
// Example:
// Input: n = 2, edges = [[1,2,7]], queries = [[2,2],[1,1,2,4],[2,2]]
//
// Output: [7,4]
//
// Explanation:
//
//
//
//
// 	Query [2,2]: The shortest path from root node 1 to node 2 is 7.
// 	Query [1,1,2,4]: The weight of edge (1,2) changes from 7 to 4.
// 	Query [2,2]: The shortest path from root node 1 to node 2 is 4.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi, wi]
// 	1 <= ui, vi <= n
// 	1 <= wi <= 104
// 	The input is generated such that edges represents a valid tree.
// 	1 <= queries.length == q <= 105
// 	queries[i].length == 2 or 4
// 	
// 		queries[i] == [1, u, v, w'] or,
// 		queries[i] == [2, x]
// 		1 <= u, v, x <= n
// 		(u, v) is always an edge from edges.
// 		1 <= w' <= 104
//

class Solution {
    public int[] treeQueries(int n, int[][] edges, int[][] queries) {
        Map<Integer, List<int[]>> graph = new HashMap<>();
        int[] parent = new int[n + 1];
        int[] weightToParent = new int[n + 1];
        parent[1] = -1;

        for (int[] edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];
            graph.computeIfAbsent(u, k -> new ArrayList<>()).add(new int[]{v, w});
            graph.computeIfAbsent(v, k -> new ArrayList<>()).add(new int[]{u, w});
        }

        // DFS to set parent and weightToParent
        Stack<Integer> stack = new Stack<>();
        stack.push(1);
        while (!stack.isEmpty()) {
            int node = stack.pop();
            for (int[] neighbor : graph.getOrDefault(node, new ArrayList<>())) {
                int nextNode = neighbor[0], w = neighbor[1];
                if (nextNode != parent[node]) {
                    parent[nextNode] = node;
                    weightToParent[nextNode] = w;
                    stack.push(nextNode);
                }
            }
        }

        List<Integer> resultList = new ArrayList<>();
        for (int[] query : queries) {
            if (query[0] == 1) {
                int u = query[1], v = query[2], newWeight = query[3];
                if (parent[v] == u) {
                    weightToParent[v] = newWeight;
                } else {
                    weightToParent[u] = newWeight;
                }
            } else {
                int x = query[1];
                int distance = 0;
                while (x != -1) {
                    distance += weightToParent[x];
                    x = parent[x];
                }
                resultList.add(distance);
            }
        }

        // Convert resultList to array
        int[] result = new int[resultList.size()];
        for (int i = 0; i < resultList.size(); i++) {
            result[i] = resultList.get(i);
        }
        return result;
    }
}
