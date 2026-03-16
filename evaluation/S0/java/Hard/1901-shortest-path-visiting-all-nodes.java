// Source: https://leetcode.com/problems/shortest-path-visiting-all-nodes/   |   Difficulty: Hard
//
// Problem Description:
// You have an undirected, connected graph of n nodes labeled from 0 to n - 1. You are given an array graph where graph[i] is a list of all the nodes connected with node i by an edge.
//
// Return the length of the shortest path that visits every node. You may start and stop at any node, you may revisit nodes multiple times, and you may reuse edges.
//
// Example:
// Input: graph = [[1,2,3],[0],[0],[0]]
// Output: 4
// Explanation: One possible path is [1,0,2,0,3]
//
// Constraints:
// n == graph.length
// 	1 <= n <= 12
// 	0 <= graph[i].length < n
// 	graph[i] does not contain i.
// 	If graph[a] contains b, then graph[b] contains a.
// 	The input graph is always connected.
//

class Solution {
    public int shortestPathLength(int[][] graph) {
        int n = graph.length;
        int finalState = (1 << n) - 1;
        Queue<int[]> queue = new LinkedList<>();
        boolean[][] visited = new boolean[n][1 << n];

        for (int i = 0; i < n; i++) {
            int state = 1 << i;
            queue.offer(new int[]{i, state, 0});
            visited[i][state] = true;
        }

        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            int node = curr[0];
            int state = curr[1];
            int dist = curr[2];

            if (state == finalState) {
                return dist;
            }

            for (int neighbor : graph[node]) {
                int nextState = state | (1 << neighbor);
                if (!visited[neighbor][nextState]) {
                    visited[neighbor][nextState] = true;
                    queue.offer(new int[]{neighbor, nextState, dist + 1});
                }
            }
        }

        return -1; // This line should never be reached         
    }
}
