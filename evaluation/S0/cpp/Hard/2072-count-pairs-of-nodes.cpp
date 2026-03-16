// Source: https://leetcode.com/problems/count-pairs-of-nodes/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected graph defined by an integer n, the number of nodes, and a 2D integer array edges, the edges in the graph, where edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi. You are also given an integer array queries.
//
// Let incident(a, b) be defined as the number of edges that are connected to either node a or b.
//
// The answer to the jth query is the number of pairs of nodes (a, b) that satisfy both of the following conditions:
//
//
// 	a < b
// 	incident(a, b) > queries[j]
//
//
// Return an array answers such that answers.length == queries.length and answers[j] is the answer of the jth query.
//
// Note that there can be multiple edges between the same two nodes.
//
// Example:
// Input: n = 4, edges = [[1,2],[2,4],[1,3],[2,3],[2,1]], queries = [2,3]
// Output: [6,5]
// Explanation: The calculations for incident(a, b) are shown in the table above.
// The answers for each of the queries are as follows:
// - answers[0] = 6. All the pairs have an incident(a, b) value greater than 2.
// - answers[1] = 5. All the pairs except (3, 4) have an incident(a, b) value greater than 3.
//
// Constraints:
// 2 <= n <= 2 * 104
// 	1 <= edges.length <= 105
// 	1 <= ui, vi <= n
// 	ui != vi
// 	1 <= queries.length <= 20
// 	0 <= queries[j] < edges.length
//

class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int> degree(n + 1, 0);
        unordered_map<long long, int> edgeCount;
        
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            degree[u]++;
            degree[v]++;
            long long key = min(u, v) * 200001LL + max(u, v);
            edgeCount[key]++;
        }
        
        vector<int> sortedDegree(degree.begin() + 1, degree.end());
        sort(sortedDegree.begin(), sortedDegree.end());
        
        vector<int> result;
        
        for (int q : queries) {
            int count = 0;
            int left = 0, right = n - 1;
            
            while (left < right) {
                if (sortedDegree[left] + sortedDegree[right] > q) {
                    count += (right - left);
                    right--;
                } else {
                    left++;
                }
            }
            
            for (const auto& [key, cnt] : edgeCount) {
                int u = key / 200001;
                int v = key % 200001;
                if (degree[u] + degree[v] > q && degree[u] + degree[v] - cnt <= q) {
                    count--;
                }
            }
            
            result.push_back(count);
        }
        
        return result;          
    }
};
