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

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> graph(n + 1);
        for (const auto& time : times) {
            graph[time[0]].emplace_back(time[1], time[2]);
        }

        vector<int> dist(n + 1, INT_MAX);
        dist[k] = 0;
        using PII = pair<int, int>;
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        pq.emplace(0, k);

        while (!pq.empty()) {
            auto [curDist, node] = pq.top();
            pq.pop();

            if (curDist > dist[node]) continue;

            for (const auto& [neighbor, weight] : graph[node]) {
                if (dist[node] + weight < dist[neighbor]) {
                    dist[neighbor] = dist[node] + weight;
                    pq.emplace(dist[neighbor], neighbor);
                }
            }
        }

        int maxDist = 0;
        for (int i = 1; i <= n; ++i) {
            if (dist[i] == INT_MAX) return -1;
            maxDist = max(maxDist, dist[i]);
        }

        return maxDist;         
    }
};
