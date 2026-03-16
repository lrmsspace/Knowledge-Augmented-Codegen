// Source: https://leetcode.com/problems/network-delay-time/   |   Difficulty: Medium
//
// Problem Description:
// You are given a network of n nodes, labeled from 1 to n. You are also given times, a list of travel times as directed edges times[i] = (ui, vi, wi), where ui is the source node, vi is the target node, and wi is the time it takes for a signal to travel from source to target.
//
// We will send a signal from a given node k. Return the minimum time it takes for all the n nodes to receive the signal. If it is impossible for all the n nodes to receive the signal, return -1.
//
// Example:
// Input: times = [[2,1,1],[2,3,1],[3,4,1]], n = 4, k = 2
// Output: 2
//
// Constraints:
// 1 <= k <= n <= 100
// 	1 <= times.length <= 6000
// 	times[i].length == 3
// 	1 <= ui, vi <= n
// 	ui != vi
// 	0 <= wi <= 100
// 	All the pairs (ui, vi) are unique. (i.e., no multiple edges.)
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int networkDelayTime(int[][] times, int n, int k) {
        // Create a graph from the times input
        Map<Integer, List<int[]>> graph = new HashMap<>();
        for (int[] time : times) {
            graph.computeIfAbsent(time[0], x -> new ArrayList<>()).add(new int[]{time[1], time[2]});
        }

        // Use Dijkstra's algorithm to find the shortest path from k to all other nodes
        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[1]));
        pq.offer(new int[]{k, 0});
        Map<Integer, Integer> dist = new HashMap<>();

        while (!pq.isEmpty()) {
            int[] current = pq.poll();
            int node = current[0];
            int time = current[1];

            if (dist.containsKey(node)) continue; // Skip if we already have a shorter path
            dist.put(node, time);

            if (graph.containsKey(node)) {
                for (int[] neighbor : graph.get(node)) {
                    int nextNode = neighbor[0];
                    int travelTime = neighbor[1];
                    if (!dist.containsKey(nextNode)) {
                        pq.offer(new int[]{nextNode, time + travelTime});
                    }
                }
            }
        }

        // Check if all nodes received the signal and find the maximum time
        if (dist.size() != n) return -1; // Not all nodes received the signal
        return Collections.max(dist.values());          
    }
}
