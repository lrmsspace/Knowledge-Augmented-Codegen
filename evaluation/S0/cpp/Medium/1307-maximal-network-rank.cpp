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

class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        vector<int> degree(n, 0);
        unordered_set<long long> roadSet;

        for (const auto& road : roads) {
            int a = road[0];
            int b = road[1];
            degree[a]++;
            degree[b]++;
            long long code = ((long long)min(a, b) << 32) | max(a, b);
            roadSet.insert(code);
        }

        int maxRank = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int currentRank = degree[i] + degree[j];
                long long code = ((long long)min(i, j) << 32) | max(i, j);
                if (roadSet.count(code)) {
                    currentRank--;
                }
                maxRank = max(maxRank, currentRank);
            }
        }

        return maxRank;         
    }
};
