// Source: https://leetcode.com/problems/count-pairs-of-nodes/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph defined by an integer n, the number of nodes, and a 2D integer array edges, the edges in the graph, where edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi. You are also given an integer array queries.
//
// Let incident(a, b) be defined as the number of edges that are connected to either node a or b.
//
// The answer to the jth query is the number of pairs of nodes (a, b) that satisfy both of the following conditions:
//
//
// 	a < b
// 	incident(a, b) > queries[j]
//
//
// Return an array answers such that answers.length == queries.length and answers[j] is the answer of the jth query.
//
// Note that there can be multiple edges between the same two nodes.
//
// Example:
// Input: n = 4, edges = [[1,2],[2,4],[1,3],[2,3],[2,1]], queries = [2,3]
// Output: [6,5]
// Explanation: The calculations for incident(a, b) are shown in the table above.
// The answers for each of the queries are as follows:
// - answers[0] = 6. All the pairs have an incident(a, b) value greater than 2.
// - answers[1] = 5. All the pairs except (3, 4) have an incident(a, b) value greater than 3.
//
// Constraints:
// 2 <= n <= 2 * 104
// 	1 <= edges.length <= 105
// 	1 <= ui, vi <= n
// 	ui != vi
// 	1 <= queries.length <= 20
// 	0 <= queries[j] < edges.length
//

class Solution {
    public int[] countPairs(int n, int[][] edges, int[] queries) {
        int m = edges.length;
        int[] degree = new int[n];
        Map<Long, Integer> edgeCount = new HashMap<>();

        for (int[] edge : edges) {
            int u = edge[0] - 1;
            int v = edge[1] - 1;
            degree[u]++;
            degree[v]++;
            long key = Math.min(u, v) * (long) n + Math.max(u, v);
            edgeCount.put(key, edgeCount.getOrDefault(key, 0) + 1);
        }

        int[] sortedDegree = degree.clone();
        Arrays.sort(sortedDegree);

        int[] result = new int[queries.length];
        for (int q = 0; q < queries.length; q++) {
            int query = queries[q];
            int count = 0;

            // Two-pointer technique to count pairs
            int left = 0, right = n - 1;
            while (left < right) {
                if (sortedDegree[left] + sortedDegree[right] > query) {
                    count += right - left;
                    right--;
                } else {
                    left++;
                }
            }

            // Adjust count for overcounted pairs
            for (Map.Entry<Long, Integer> entry : edgeCount.entrySet()) {
                long key = entry.getKey();
                int u = (int) (key / n);
                int v = (int) (key % n);
                int sharedEdges = entry.getValue();
                if (degree[u] + degree[v] > query && degree[u] + degree[v] - sharedEdges <= query) {
                    count--;
                }
            }

            result[q] = count;
        }

        return result;          
    }
}
