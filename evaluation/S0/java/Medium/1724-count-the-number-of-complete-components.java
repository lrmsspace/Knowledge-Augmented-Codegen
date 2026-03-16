// Source: https://leetcode.com/problems/count-the-number-of-complete-components/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n. There is an undirected graph with n vertices, numbered from 0 to n - 1. You are given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting vertices ai and bi.
//
// Return the number of complete connected components of the graph.
//
// A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
//
// A connected component is said to be complete if there exists an edge between every pair of its vertices.
//
// Example:
// Input: n = 6, edges = [[0,1],[0,2],[1,2],[3,4]]
// Output: 3
// Explanation: From the picture above, one can see that all of the components of this graph are complete.
//
// Constraints:
// 1 <= n <= 50
// 	0 <= edges.length <= n * (n - 1) / 2
// 	edges[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
// 	There are no repeated edges.
//

class Solution {
    public int countCompleteComponents(int n, int[][] edges) {
        List<Set<Integer>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new HashSet<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }

        boolean[] visited = new boolean[n];
        int completeComponents = 0;

        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                Set<Integer> componentNodes = new HashSet<>();
                dfs(i, graph, visited, componentNodes);

                int size = componentNodes.size();
                int expectedEdges = size * (size - 1) / 2;
                int actualEdges = 0;

                for (int node : componentNodes) {
                    actualEdges += graph.get(node).size();
                }
                actualEdges /= 2; // Each edge is counted twice

                if (actualEdges == expectedEdges) {
                    completeComponents++;
                }
            }
        }

        return completeComponents;          
    }
}
