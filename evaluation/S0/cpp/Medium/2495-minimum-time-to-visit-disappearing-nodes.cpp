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
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        vector<vector<pair<int, int>>> graph(n);
        for (const auto& edge : edges) {
            graph[edge[0]].emplace_back(edge[1], edge[2]);
            graph[edge[1]].emplace_back(edge[0], edge[2]);
        }

        vector<int> minTime(n, INT_MAX);
        minTime[0] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, 0); // (time, node)

        while (!pq.empty()) {
            auto [currTime, node] = pq.top();
            pq.pop();

            if (currTime > minTime[node]) continue;

            for (const auto& [neighbor, length] : graph[node]) {
                int arrivalTime = currTime + length;
                if (arrivalTime < disappear[neighbor] && arrivalTime < minTime[neighbor]) {
                    minTime[neighbor] = arrivalTime;
                    pq.emplace(arrivalTime, neighbor);
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (minTime[i] == INT_MAX) {
                minTime[i] = -1;
            }
        }

        return minTime;         
    }
};
