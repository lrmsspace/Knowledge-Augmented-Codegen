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

int maximalNetworkRank(int n, int** roads, int roadsSize, int* roadsColSize) {
    int degree[n];
    bool connected[n][n];
    memset(degree, 0, sizeof(degree));
    memset(connected, false, sizeof(connected));

    for (int i = 0; i < roadsSize; i++) {
        int a = roads[i][0];
        int b = roads[i][1];
        degree[a]++;
        degree[b]++;
        connected[a][b] = true;
        connected[b][a] = true;
    }

    int maxRank = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int currentRank = degree[i] + degree[j];
            if (connected[i][j]) {
                currentRank--;
            }
            if (currentRank > maxRank) {
                maxRank = currentRank;
            }
        }
    }

    return maxRank;     
}
