// Source: https://leetcode.com/problems/minimum-time-to-visit-disappearing-nodes/   |   Difficulty: Medium
//
// Problem Description:
// There is an undirected graph of n nodes. You are given a 2D array edges, where edges[i] = [ui, vi, lengthi] describes an edge between node ui and node vi with a traversal time of lengthi units.
//
// Additionally, you are given an array disappear, where disappear[i] denotes the time when the node i disappears from the graph and you won't be able to visit it.
//
// Note that the graph might be disconnected and might contain multiple edges.
//
// Return the array answer, with answer[i] denoting the minimum units of time required to reach node i from node 0. If node i is unreachable from node 0 then answer[i] is -1.
//
// Example:
// Input: n = 3, edges = [[0,1,2],[1,2,1],[0,2,4]], disappear = [1,1,5]
//
// Output: [0,-1,4]
//
// Explanation:
//
//
//
// We are starting our journey from node 0, and our goal is to find the minimum time required to reach each node before it disappears.
//
//
// 	For node 0, we don't need any time as it is our starting point.
// 	For node 1, we need at least 2 units of time to traverse edges[0]. Unfortunately, it disappears at that moment, so we won't be able to visit it.
// 	For node 2, we need at least 4 units of time to traverse edges[2].
//
// Constraints:
// 1 <= n <= 5 * 104
// 	0 <= edges.length <= 105
// 	edges[i] == [ui, vi, lengthi]
// 	0 <= ui, vi <= n - 1
// 	1 <= lengthi <= 105
// 	disappear.length == n
// 	1 <= disappear[i] <= 105
//

class Solution {
    public int[] minimumTime(int n, int[][] edges, int[] disappear) {
        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(new int[]{edge[1], edge[2]});
            graph.get(edge[1]).add(new int[]{edge[0], edge[2]});
        }

        int[] dist = new int[n];
        Arrays.fill(dist, Integer.MAX_VALUE);
        dist[0] = 0;

        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[1]));
        pq.offer(new int[]{0, 0});

        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int node = curr[0];
            int time = curr[1];

            if (time > dist[node]) {
                continue;
            }

            for (int[] neighbor : graph.get(node)) {
                int nextNode = neighbor[0];
                int travelTime = neighbor[1];
                int arrivalTime = time + travelTime;

                if (arrivalTime < disappear[nextNode] && arrivalTime < dist[nextNode]) {
                    dist[nextNode] = arrivalTime;
                    pq.offer(new int[]{nextNode, arrivalTime});
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (dist[i] == Integer.MAX_VALUE) {
                dist[i] = -1;
            }
        }

        return dist;            
    }
}
