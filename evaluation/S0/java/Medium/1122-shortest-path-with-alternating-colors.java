// Source: https://leetcode.com/problems/shortest-path-with-alternating-colors/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n, the number of nodes in a directed graph where the nodes are labeled from 0 to n - 1. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.
//
// You are given two arrays redEdges and blueEdges where:
//
//
// 	redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in the graph, and
// 	blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in the graph.
//
//
// Return an array answer of length n, where each answer[x] is the length of the shortest path from node 0 to node x such that the edge colors alternate along the path, or -1 if such a path does not exist.
//
// Example:
// Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
// Output: [0,1,-1]
//
// Constraints:
// 1 <= n <= 100
// 	0 <= redEdges.length, blueEdges.length <= 400
// 	redEdges[i].length == blueEdges[j].length == 2
// 	0 <= ai, bi, uj, vj < n
//

class Solution {
    public int[] shortestAlternatingPaths(int n, int[][] redEdges, int[][] blueEdges) {
        List<List<Integer>> redGraph = new ArrayList<>();
        List<List<Integer>> blueGraph = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            redGraph.add(new ArrayList<>());
            blueGraph.add(new ArrayList<>());
        }

        for (int[] edge : redEdges) {
            redGraph.get(edge[0]).add(edge[1]);
        }

        for (int[] edge : blueEdges) {
            blueGraph.get(edge[0]).add(edge[1]);
        }

        int[] result = new int[n];
        Arrays.fill(result, -1);
        result[0] = 0;

        Queue<int[]> queue = new LinkedList<>();
        queue.offer(new int[]{0, 0}); // node, color (0: red, 1: blue)
        queue.offer(new int[]{0, 1});

        boolean[][] visited = new boolean[n][2];
        visited[0][0] = true;
        visited[0][1] = true;

        int steps = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                int[] current = queue.poll();
                int node = current[0];
                int color = current[1];

                if (color == 0) { // last edge was red, so we can go to blue edges
                    for (int neighbor : blueGraph.get(node)) {
                        if (!visited[neighbor][1]) {
                            visited[neighbor][1] = true;
                            queue.offer(new int[]{neighbor, 1});
                            if (result[neighbor] == -1) {
                                result[neighbor] = steps + 1;
                            }
                        }
                    }
                } else { // last edge was blue, so we can go to red edges
                    for (int neighbor : redGraph.get(node)) {
                        if (!visited[neighbor][0]) {
                            visited[neighbor][0] = true;
                            queue.offer(new int[]{neighbor, 0});
                            if (result[neighbor] == -1) {
                                result[neighbor] = steps + 1;
                            }
                        }
                    }
                }
            }
            steps++;
        }

        return result;          
    }
}
