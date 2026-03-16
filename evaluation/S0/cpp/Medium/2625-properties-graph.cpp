// Source: https://leetcode.com/problems/properties-graph/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array properties having dimensions n x m and an integer k.
//
// Define a function intersect(a, b) that returns the number of distinct integers common to both arrays a and b.
//
// Construct an undirected graph where each index i corresponds to properties[i]. There is an edge between node i and node j if and only if intersect(properties[i], properties[j]) >= k, where i and j are in the range [0, n - 1] and i != j.
//
// Return the number of connected components in the resulting graph.
//
// Example:
// Input: properties = [[1,2],[1,1],[3,4],[4,5],[5,6],[7,7]], k = 1
//
// Output: 3
//
// Explanation:
//
// The graph formed has 3 connected components:
//
// Constraints:
// 1 <= n == properties.length <= 100
// 	1 <= m == properties[i].length <= 100
// 	1 <= properties[i][j] <= 100
// 	1 <= k <= m
//

class Solution {
public:
    int numberOfComponents(vector<vector<int>>& properties, int k) {
        int n = properties.size();
        vector<unordered_set<int>> graph(n);
        
        // Build the graph
        for (int i = 0; i < n; ++i) {
            unordered_set<int> setA(properties[i].begin(), properties[i].end());
            for (int j = i + 1; j < n; ++j) {
                int commonCount = 0;
                for (int val : properties[j]) {
                    if (setA.count(val)) {
                        commonCount++;
                        if (commonCount >= k) {
                            graph[i].insert(j);
                            graph[j].insert(i);
                            break;
                        }
                    }
                }
            }
        }

        // DFS to count connected components
        vector<bool> visited(n, false);
        int components = 0;

        function<void(int)> dfs = [&](int node) {
            visited[node] = true;
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    dfs(neighbor);
                }
            }
        };

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                components++;
                dfs(i);
            }
        }

        return components;          
    }
};
