// Source: https://leetcode.com/problems/maximal-network-rank/   |   Difficulty: Medium
//
// Problem Description:
// There is an infrastructure of n cities with some number of roads connecting these cities. Each roads[i] = [ai, bi] indicates that there is a bidirectional road between cities ai and bi.
//
// The network rank of two different cities is defined as the total number of directly connected roads to either city. If a road is directly connected to both cities, it is only counted once.
//
// The maximal network rank of the infrastructure is the maximum network rank of all pairs of different cities.
//
// Given the integer n and the array roads, return the maximal network rank of the entire infrastructure.
//
// Example:
// Input: n = 4, roads = [[0,1],[0,3],[1,2],[1,3]]
// Output: 4
// Explanation: The network rank of cities 0 and 1 is 4 as there are 4 roads that are connected to either 0 or 1. The road between 0 and 1 is only counted once.
//
// Constraints:
// 2 <= n <= 100
// 	0 <= roads.length <= n * (n - 1) / 2
// 	roads[i].length == 2
// 	0 <= ai, bi <= n-1
// 	ai != bi
// 	Each pair of cities has at most one road connecting them.
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
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        vector<int> degree(n, 0);
        unordered_set<string> roadSet;

        for (const auto& road : roads) {
            int a = road[0], b = road[1];
            degree[a]++;
            degree[b]++;
            roadSet.insert(to_string(min(a, b)) + "," + to_string(max(a, b)));
        }

        int maxRank = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int rank = degree[i] + degree[j];
                if (roadSet.count(to_string(i) + "," + to_string(j))) {
                    rank--; // Subtract one if there is a direct road between i and j
                }
                maxRank = max(maxRank, rank);
            }
        }

        return maxRank;         
    }
};
