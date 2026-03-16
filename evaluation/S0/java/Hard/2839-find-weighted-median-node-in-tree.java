// Source: https://leetcode.com/problems/find-weighted-median-node-in-tree/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an undirected, weighted tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an edge from node ui to vi with weight wi.
//
// The weighted median node is defined as the first node x on the path from ui to vi such that the sum of edge weights from ui to x is greater than or equal to half of the total path weight.
//
// You are given a 2D integer array queries. For each queries[j] = [uj, vj], determine the weighted median node along the path from uj to vj.
//
// Return an array ans, where ans[j] is the node index of the weighted median for queries[j].
//
// Example:
// Input: n = 2, edges = [[0,1,7]], queries = [[1,0],[0,1]]
//
// Output: [0,1]
//
// Explanation:
//
//
//
//
// 	
// 		
// 			Query
// 			Path
// 			Edge
// 			Weights
// 			Total
// 			Path
// 			Weight
// 			Half
// 			Explanation
// 			Answer
// 		
// 	
// 	
// 		
// 			[1, 0]
// 			1 → 0
// 			[7]
// 			7
// 			3.5
// 			Sum from 1 → 0 = 7 >= 3.5, median is node 0.
// 			0
// 		
// 		
// 			[0, 1]
// 			0 → 1
// 			[7]
// 			7
// 			3.5
// 			Sum from 0 → 1 = 7 >= 3.5, median is node 1.
// 			1
//
// Constraints:
// 2 <= n <= 105
// 	edges.length == n - 1
// 	edges[i] == [ui, vi, wi]
// 	0 <= ui, vi < n
// 	1 <= wi <= 109
// 	1 <= queries.length <= 105
// 	queries[j] == [uj, vj]
// 	0 <= uj, vj < n
// 	The input is generated such that edges represents a valid tree.
//

class Solution {
    public int[] findMedian(int n, int[][] edges, int[][] queries) {
        List<List<long[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(new long[]{edge[1], edge[2]});
            graph.get(edge[1]).add(new long[]{edge[0], edge[2]});
        }

        int LOG = 17;
        int[][] parent = new int[LOG][n];
        long[] depth = new long[n];
        int[] level = new int[n];

        // DFS to populate parent, depth, and level arrays
        Deque<Integer> stack = new ArrayDeque<>();
        stack.push(0);
        boolean[] visited = new boolean[n];
        visited[0] = true;

        while (!stack.isEmpty()) {
            int node = stack.pop();
            for (long[] neighbor : graph.get(node)) {
                int nextNode = (int) neighbor[0];
                long weight = neighbor[1];
                if (!visited[nextNode]) {
                    visited[nextNode] = true;
                    parent[0][nextNode] = node;
                    depth[nextNode] = depth[node] + weight;
                    level[nextNode] = level[node] + 1;
                    stack.push(nextNode);
                }
            }
        }

        // Precompute 2^i th ancestors
        for (int i = 1; i < LOG; i++) {
            for (int j = 0; j < n; j++) {
                parent[i][j] = parent[i - 1][parent[i - 1][j]];
            }
        }

        // Function to find LCA
        BiFunction<Integer, Integer, Integer> lca = (u, v) -> {
            if (level[u] < level[v]) {
                int temp = u;
                u = v;
                v = temp;
            }
            for (int i = LOG - 1; i >= 0; i--) {
                if (level[u] - (1 << i) >= level[v]) {
                    u = parent[i][u];
                }
            }
            if (u == v) return u;
            for (int i = LOG - 1; i >= 0; i--) {
                if (parent[i][u] != parent[i][v]) {
                    u = parent[i][u];
                    v = parent[i][v];
                }
            }
            return parent[0][u];
        };
        int[] result = new int[queries.length];
        for (int i = 0; i < queries.length; i++) {
            int u = queries[i][0];
            int v = queries[i][1];
            int ancestor = lca.apply(u, v);
            long totalWeight = depth[u] + depth[v] - 2 * depth[ancestor];
            long halfWeight = totalWeight / 2;

            // Move from u to ancestor
            int currentNode = u;
            for (int j = LOG - 1; j >= 0; j--) {
                if (level[currentNode] - (1 << j) >= level[ancestor]) {
                    long nextDepth = depth[parent[j][currentNode]];
                    if (depth[u] - nextDepth <= halfWeight) {
                        currentNode = parent[j][currentNode];
                    }
                }
            }

            if (depth[u] - depth[currentNode] >= halfWeight) {
                result[i] = currentNode;
            } else {
                // Move from v to ancestor
                currentNode = v;
                for (int j = LOG - 1; j >= 0; j--) {
                    if (level[currentNode] - (1 << j) >= level[ancestor]) {
                        long nextDepth = depth[parent[j][currentNode]];
                        if (depth[v] - nextDepth <= halfWeight) {
                            currentNode = parent[j][currentNode];
                        }
                    }
                }
                result[i] = currentNode;
            }
        }
        return result;
    }
        }
