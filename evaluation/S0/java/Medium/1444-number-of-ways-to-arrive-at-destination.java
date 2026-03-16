// Source: https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/   |   Difficulty: Medium
//
// Problem Description:
// You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional roads between some intersections. The inputs are generated such that you can reach any intersection from any other intersection and that there is at most one road between any two intersections.
//
// You are given an integer n and a 2D integer array roads where roads[i] = [ui, vi, timei] means that there is a road between intersections ui and vi that takes timei minutes to travel. You want to know in how many ways you can travel from intersection 0 to intersection n - 1 in the shortest amount of time.
//
// Return the number of ways you can arrive at your destination in the shortest amount of time. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
// Output: 4
// Explanation: The shortest amount of time it takes to go from intersection 0 to intersection 6 is 7 minutes.
// The four ways to get there in 7 minutes are:
// - 0 ➝ 6
// - 0 ➝ 4 ➝ 6
// - 0 ➝ 1 ➝ 2 ➝ 5 ➝ 6
// - 0 ➝ 1 ➝ 3 ➝ 5 ➝ 6
//
// Constraints:
// 1 <= n <= 200
// 	n - 1 <= roads.length <= n * (n - 1) / 2
// 	roads[i].length == 3
// 	0 <= ui, vi <= n - 1
// 	1 <= timei <= 109
// 	ui != vi
// 	There is at most one road connecting any two intersections.
// 	You can reach any intersection from any other intersection.
//

class Solution {
    public int countPaths(int n, int[][] roads) {
        final int MOD = 1_000_000_007;

        List<List<int[]>> graph = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] road : roads) {
            graph.get(road[0]).add(new int[]{road[1], road[2]});
            graph.get(road[1]).add(new int[]{road[0], road[2]});
        }

        long[] dist = new long[n];
        Arrays.fill(dist, Long.MAX_VALUE);
        dist[0] = 0;

        int[] ways = new int[n];
        ways[0] = 1;

        PriorityQueue<long[]> pq = new PriorityQueue<>(Comparator.comparingLong(a -> a[0]));
        pq.offer(new long[]{0, 0}); // {distance, node}

        while (!pq.isEmpty()) {
            long[] curr = pq.poll();
            long currDist = curr[0];
            int currNode = (int) curr[1];

            if (currDist > dist[currNode]) {
                continue;
            }

            for (int[] neighbor : graph.get(currNode)) {
                int nextNode = neighbor[0];
                long time = neighbor[1];

                if (currDist + time < dist[nextNode]) {
                    dist[nextNode] = currDist + time;
                    ways[nextNode] = ways[currNode];
                    pq.offer(new long[]{dist[nextNode], nextNode});
                } else if (currDist + time == dist[nextNode]) {
                    ways[nextNode] = (ways[nextNode] + ways[currNode]) % MOD;
                }
            }
        }

        return ways[n - 1];         
    }
}
