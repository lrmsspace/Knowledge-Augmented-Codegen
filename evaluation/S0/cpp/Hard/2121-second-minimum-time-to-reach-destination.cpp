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
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        vector<vector<int>> graph(n + 1);
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        // minTime[node][0] = minimum time to reach node
        // minTime[node][1] = second minimum time to reach node
        vector<vector<int>> minTime(n + 1, vector<int>(2, INT_MAX));
        minTime[1][0] = 0;
        
        // Min-heap priority queue: (current_time, node)
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, 1});
        
        while (!pq.empty()) {
            auto [currTime, node] = pq.top();
            pq.pop();
            
            for (int neighbor : graph[node]) {
                int waitTime = 0;
                if ((currTime / change) % 2 == 1) {
                    waitTime = change - (currTime % change);
                }
                int arrivalTime = currTime + waitTime + time;
                
                if (arrivalTime < minTime[neighbor][0]) {
                    minTime[neighbor][1] = minTime[neighbor][0];
                    minTime[neighbor][0] = arrivalTime;
                    pq.push({arrivalTime, neighbor});
                } else if (arrivalTime > minTime[neighbor][0] && arrivalTime < minTime[neighbor][1]) {
                    minTime[neighbor][1] = arrivalTime;
                    pq.push({arrivalTime, neighbor});
                }
            }
        }
        
        return minTime[n][1];           
    }
};
