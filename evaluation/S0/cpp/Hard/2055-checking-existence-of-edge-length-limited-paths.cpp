// Source: https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/   |   Difficulty: Hard
//
// Problem Description:
// An undirected graph of n nodes is defined by edgeList, where edgeList[i] = [ui, vi, disi] denotes an edge between nodes ui and vi with distance disi. Note that there may be multiple edges between two nodes.
//
// Given an array queries, where queries[j] = [pj, qj, limitj], your task is to determine for each queries[j] whether there is a path between pj and qj such that each edge on the path has a distance strictly less than limitj .
//
// Return a boolean array answer, where answer.length == queries.length and the jth value of answer is true if there is a path for queries[j] is true, and false otherwise.
//
// Example:
// Input: n = 3, edgeList = [[0,1,2],[1,2,4],[2,0,8],[1,0,16]], queries = [[0,1,2],[0,2,5]]
// Output: [false,true]
// Explanation: The above figure shows the given graph. Note that there are two overlapping edges between 0 and 1 with distances 2 and 16.
// For the first query, between 0 and 1 there is no path where each distance is less than 2, thus we return false for this query.
// For the second query, there is a path (0 -> 1 -> 2) of two edges with distances less than 5, thus we return true for this query.
//
// Constraints:
// 2 <= n <= 105
// 	1 <= edgeList.length, queries.length <= 105
// 	edgeList[i].length == 3
// 	queries[j].length == 3
// 	0 <= ui, vi, pj, qj <= n - 1
// 	ui != vi
// 	pj != qj
// 	1 <= disi, limitj <= 109
// 	There may be multiple edges between two nodes.
//

class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        // Union-Find data structure
        vector<int> parent(n);
        for (int i = 0; i < n; i++) parent[i] = i;
        
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };
        
        auto unionSet = [&](int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                parent[rootY] = rootX;
            }
        };
        
        // Sort edges by distance
        sort(edgeList.begin(), edgeList.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });
        
        // Prepare queries with original indices
        int qSize = queries.size();
        vector<pair<vector<int>, int>> indexedQueries;
        for (int i = 0; i < qSize; i++) {
            indexedQueries.push_back({queries[i], i});
        }
        
        // Sort queries by limit
        sort(indexedQueries.begin(), indexedQueries.end(), [](const pair<vector<int>, int>& a, const pair<vector<int>, int>& b) {
            return a.first[2] < b.first[2];
        });
        
        vector<bool> result(qSize, false);
        int edgeIdx = 0;
        
        // Process each query
        for (const auto& [query, idx] : indexedQueries) {
            int p = query[0];
            int q = query[1];
            int limit = query[2];
            
            // Union edges with distance less than limit
            while (edgeIdx < edgeList.size() && edgeList[edgeIdx][2] < limit) {
                unionSet(edgeList[edgeIdx][0], edgeList[edgeIdx][1]);
                edgeIdx++;
            }
            
            // Check if p and q are connected
            if (find(p) == find(q)) {
                result[idx] = true;
            }
        }
        
        return result;          
    }
};
