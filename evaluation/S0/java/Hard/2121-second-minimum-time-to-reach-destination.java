// Source: https://leetcode.com/problems/second-minimum-time-to-reach-destination/   |   Difficulty: Hard
//
// Problem Description:
// A city is represented as a bi-directional connected graph with n vertices where each vertex is labeled from 1 to n (inclusive). The edges in the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a bi-directional edge between vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself. The time taken to traverse any edge is time minutes.
//
// Each vertex has a traffic signal which changes its color from green to red and vice versa every change minutes. All signals change at the same time. You can enter a vertex at any time, but can leave a vertex only when the signal is green. You cannot wait at a vertex if the signal is green.
//
// The second minimum value is defined as the smallest value strictly larger than the minimum value.
//
//
// 	For example the second minimum value of [2, 3, 4] is 3, and the second minimum value of [2, 2, 4] is 4.
//
//
// Given n, edges, time, and change, return the second minimum time it will take to go from vertex 1 to vertex n.
//
// Example:
// Input: n = 5, edges = [[1,2],[1,3],[1,4],[3,4],[4,5]], time = 3, change = 5
// Output: 13
// Explanation:
// The figure on the left shows the given graph.
// The blue path in the figure on the right is the minimum time path.
// The time taken is:
// - Start at 1, time elapsed=0
// - 1 -> 4: 3 minutes, time elapsed=3
// - 4 -> 5: 3 minutes, time elapsed=6
// Hence the minimum time needed is 6 minutes.
//
// The red path shows the path to get the second minimum time.
// - Start at 1, time elapsed=0
// - 1 -> 3: 3 minutes, time elapsed=3
// - 3 -> 4: 3 minutes, time elapsed=6
// - Wait at 4 for 4 minutes, time elapsed=10
// - 4 -> 5: 3 minutes, time elapsed=13
// Hence the second minimum time is 13 minutes.
//
// Constraints:
// 2 <= n <= 104
// 	n - 1 <= edges.length <= min(2 * 104, n * (n - 1) / 2)
// 	edges[i].length == 2
// 	1 <= ui, vi <= n
// 	ui != vi
// 	There are no duplicate edges.
// 	Each vertex can be reached directly or indirectly from every other vertex.
// 	1 <= time, change <= 103
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int secondMinimum(int n, int[][] edges, int time, int change) {
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }

        int[][] dist = new int[n + 1][2];
        for (int i = 0; i <= n; i++) {
            Arrays.fill(dist[i], Integer.MAX_VALUE);
        }
        dist[1][0] = 0;

        Queue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[1]));
        pq.offer(new int[]{1, 0});

        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int node = curr[0];
            int currTime = curr[1];

            for (int neighbor : graph.get(node)) {
                int waitTime = (currTime / change) % 2 == 1 ? change - (currTime % change) : 0;
                int arrivalTime = currTime + waitTime + time;

                if (arrivalTime < dist[neighbor][0]) {
                    dist[neighbor][0] = arrivalTime;
                    pq.offer(new int[]{neighbor, arrivalTime});
                } else if (arrivalTime > dist[neighbor][0] && arrivalTime < dist[neighbor][1]) {
                    dist[neighbor][1] = arrivalTime;
                    pq.offer(new int[]{neighbor, arrivalTime});
                }
            }
        }

        return dist[n][1];          
    }
}
