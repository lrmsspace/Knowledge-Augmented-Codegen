// Source: https://leetcode.com/problems/maximum-points-tourist-can-earn/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers, n and k, along with two 2D integer arrays, stayScore and travelScore.
//
// A tourist is visiting a country with n cities, where each city is directly connected to every other city. The tourist's journey consists of exactly k 0-indexed days, and they can choose any city as their starting point.
//
// Each day, the tourist has two choices:
//
//
// 	Stay in the current city: If the tourist stays in their current city curr during day i, they will earn stayScore[i][curr] points.
// 	Move to another city: If the tourist moves from their current city curr to city dest, they will earn travelScore[curr][dest] points.
//
//
// Return the maximum possible points the tourist can earn.
//
// Example:
// Input: n = 2, k = 1, stayScore = [[2,3]], travelScore = [[0,2],[1,0]]
//
// Output: 3
//
// Explanation:
//
// The tourist earns the maximum number of points by starting in city 1 and staying in that city.
//
// Constraints:
// 1 <= n <= 200
// 	1 <= k <= 200
// 	n == travelScore.length == travelScore[i].length == stayScore[i].length
// 	k == stayScore.length
// 	1 <= stayScore[i][j] <= 100
// 	0 <= travelScore[i][j] <= 100
// 	travelScore[i][i] == 0
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
    int maxScore(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore) {
        // dp[i][j] will store the maximum points that can be earned on day i if the tourist is in city j
        vector<vector<int>> dp(k, vector<int>(n, 0));

        // Initialize the first day with stay scores
        for (int j = 0; j < n; ++j) {
            dp[0][j] = stayScore[0][j];
        }

        // Fill the dp table for subsequent days
        for (int i = 1; i < k; ++i) {
            for (int curr = 0; curr < n; ++curr) {
                // Option 1: Stay in the current city
                int stayPoints = dp[i-1][curr] + stayScore[i][curr];

                // Option 2: Move to another city
                int movePoints = 0;
                for (int dest = 0; dest < n; ++dest) {
                    if (dest != curr) {
                        movePoints = max(movePoints, dp[i-1][curr] + travelScore[curr][dest] + stayScore[i][dest]);
                    }
                }

                // Take the maximum of both options
                dp[i][curr] = max(stayPoints, movePoints);
            }
        }

        // The answer will be the maximum points on the last day across all cities
        int maxPoints = 0;
        for (int j = 0; j < n; ++j) {
            maxPoints = max(maxPoints, dp[k-1][j]);
        }

        return maxPoints;           
    }
};
