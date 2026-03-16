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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
        // Sort edges by distance
        sort(edgeList.begin(), edgeList.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });

        // Sort queries by limit and keep track of original indices
        vector<pair<vector<int>, int>> sortedQueries;
        for (int i = 0; i < queries.size(); ++i) {
            sortedQueries.emplace_back(queries[i], i);
        }
        sort(sortedQueries.begin(), sortedQueries.end(), [](const pair<vector<int>, int>& a, const pair<vector<int>, int>& b) {
            return a.first[2] < b.first[2];
        });

        // Disjoint Set Union (DSU) for union-find operations
        vector<int> parent(n), rank(n, 1);
        iota(parent.begin(), parent.end(), 0);

        function<int(int)> find = [&](int x) {
            if (parent[x] != x) {
                parent[x] = find(parent[x]);
            }
            return parent[x];
        };

        auto unite = [&](int x, int y) {
            int rootX = find(x);
            int rootY = find(y);
            if (rootX != rootY) {
                if (rank[rootX] > rank[rootY]) {
                    parent[rootY] = rootX;
                } else if (rank[rootX] < rank[rootY]) {
                    parent[rootX] = rootY;
                } else {
                    parent[rootY] = rootX;
                    rank[rootX]++;
                }
            }
        };

        vector<bool> answer(queries.size());
        int edgeIndex = 0;

        // Process each query in sorted order
        for (const auto& [query, idx] : sortedQueries) {
            int p = query[0], q = query[1], limit = query[2];

            // Unite edges that are less than the current limit
            while (edgeIndex < edgeList.size() && edgeList[edgeIndex][2] < limit) {
                unite(edgeList[edgeIndex][0], edgeList[edgeIndex][1]);
                edgeIndex++;
            }

            // Check if p and q are in the same connected component
            answer[idx] = (find(p) == find(q));
        }

        return answer;          
    }
};
