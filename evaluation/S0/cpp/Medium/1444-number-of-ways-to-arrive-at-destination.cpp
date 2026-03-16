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
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        const int MOD = 1e9 + 7;
        using PII = pair<long long, int>; // (time, node)
        vector<vector<PII>> graph(n);
        for (const auto& road : roads) {
            graph[road[0]].emplace_back(road[2], road[1]);
            graph[road[1]].emplace_back(road[2], road[0]);
        }

        priority_queue<PII, vector<PII>, greater<PII>> pq;
        pq.emplace(0, 0); // (time, node)

        vector<long long> minTime(n, LLONG_MAX);
        vector<int> ways(n, 0);
        minTime[0] = 0;
        ways[0] = 1;

        while (!pq.empty()) {
            auto [currTime, node] = pq.top();
            pq.pop();

            if (currTime > minTime[node]) continue;

            for (const auto& [time, neighbor] : graph[node]) {
                long long newTime = currTime + time;
                if (newTime < minTime[neighbor]) {
                    minTime[neighbor] = newTime;
                    ways[neighbor] = ways[node];
                    pq.emplace(newTime, neighbor);
                } else if (newTime == minTime[neighbor]) {
                    ways[neighbor] = (ways[neighbor] + ways[node]) % MOD;
                }
            }
        }

        return ways[n - 1];         
    }
};
