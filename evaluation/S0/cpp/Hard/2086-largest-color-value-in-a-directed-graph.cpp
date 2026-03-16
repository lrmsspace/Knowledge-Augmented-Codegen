// Source: https://leetcode.com/problems/largest-color-value-in-a-directed-graph/   |   Difficulty: Hard
//
// Problem Description:
// There is a directed graph of n colored nodes and m edges. The nodes are numbered from 0 to n - 1.
//
// You are given a string colors where colors[i] is a lowercase English letter representing the color of the ith node in this graph (0-indexed). You are also given a 2D array edges where edges[j] = [aj, bj] indicates that there is a directed edge from node aj to node bj.
//
// A valid path in the graph is a sequence of nodes x1 -> x2 -> x3 -> ... -> xk such that there is a directed edge from xi to xi+1 for every 1 <= i < k. The color value of the path is the number of nodes that are colored the most frequently occurring color along that path.
//
// Return the largest color value of any valid path in the given graph, or -1 if the graph contains a cycle.
//
// Example:
// Input: colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
// Output: 3
// Explanation: The path 0 -> 2 -> 3 -> 4 contains 3 nodes that are colored "a" (red in the above image).
//
// Constraints:
// n == colors.length
// 	m == edges.length
// 	1 <= n <= 105
// 	0 <= m <= 105
// 	colors consists of lowercase English letters.
// 	0 <= aj, bj < n
//

class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<vector<int>> graph(n);
        vector<int> inDegree(n, 0);
        
        for (const auto& edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            inDegree[edge[1]]++;
        }
        
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        vector<vector<int>> colorCount(n, vector<int>(26, 0));
        int visited = 0;
        int maxColorValue = 0;
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            visited++;
            
            int colorIndex = colors[node] - 'a';
            colorCount[node][colorIndex]++;
            maxColorValue = max(maxColorValue, colorCount[node][colorIndex]);
            
            for (int neighbor : graph[node]) {
                for (int c = 0; c < 26; c++) {
                    colorCount[neighbor][c] = max(colorCount[neighbor][c], colorCount[node][c]);
                }
                
                inDegree[neighbor]--;
                if (inDegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        return visited == n ? maxColorValue : -1;           
    }
};
