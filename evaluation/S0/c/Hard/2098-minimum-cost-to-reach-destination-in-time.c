// Source: https://leetcode.com/problems/minimum-cost-to-reach-destination-in-time/   |   Difficulty: Hard
//
// Problem Description:
// There is a country of n cities numbered from 0 to n - 1 where all the cities are connected by bi-directional roads. The roads are represented as a 2D integer array edges where edges[i] = [xi, yi, timei] denotes a road between cities xi and yi that takes timei minutes to travel. There may be multiple roads of differing travel times connecting the same two cities, but no road connects a city to itself.
//
// Each time you pass through a city, you must pay a passing fee. This is represented as a 0-indexed integer array passingFees of length n where passingFees[j] is the amount of dollars you must pay when you pass through city j.
//
// In the beginning, you are at city 0 and want to reach city n - 1 in maxTime minutes or less. The cost of your journey is the summation of passing fees for each city that you passed through at some moment of your journey (including the source and destination cities).
//
// Given maxTime, edges, and passingFees, return the minimum cost to complete your journey, or -1 if you cannot complete it within maxTime minutes.
//
// Example:
// Input: maxTime = 30, edges = [[0,1,10],[1,2,10],[2,5,10],[0,3,1],[3,4,10],[4,5,15]], passingFees = [5,1,2,20,20,3]
// Output: 11
// Explanation: The path to take is 0 -> 1 -> 2 -> 5, which takes 30 minutes and has $11 worth of passing fees.
//
// Constraints:
// 1 <= maxTime <= 1000
// 	n == passingFees.length
// 	2 <= n <= 1000
// 	n - 1 <= edges.length <= 1000
// 	0 <= xi, yi <= n - 1
// 	1 <= timei <= 1000
// 	1 <= passingFees[j] <= 1000 
// 	The graph may contain multiple edges between two nodes.
// 	The graph does not contain self loops.
//

int minCost(int maxTime, int** edges, int edgesSize, int* edgesColSize, int* passingFees, int passingFeesSize) {
    int n = passingFeesSize;
    int **dp = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        dp[i] = (int*)malloc((maxTime + 1) * sizeof(int));
        for (int t = 0; t <= maxTime; t++) {
            dp[i][t] = 1000000000; // Infinity
        }
    }
    dp[0][0] = passingFees[0];

    for (int t = 1; t <= maxTime; t++) {
        for (int e = 0; e < edgesSize; e++) {
            int u = edges[e][0];
            int v = edges[e][1];
            int time = edges[e][2];

            if (t >= time) {
                if (dp[u][t - time] + passingFees[v] < dp[v][t]) {
                    dp[v][t] = dp[u][t - time] + passingFees[v];
                }
                if (dp[v][t - time] + passingFees[u] < dp[u][t]) {
                    dp[u][t] = dp[v][t - time] + passingFees[u];
                }
            }
        }
    }

    int result = 1000000000;
    for (int t = 0; t <= maxTime; t++) {
        if (dp[n - 1][t] < result) {
            result = dp[n - 1][t];
        }
    }

    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return result == 1000000000 ? -1 : result;      
}
