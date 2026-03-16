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

class Solution {
public:
    int maxScore(int n, int k, vector<vector<int>>& stayScore, vector<vector<int>>& travelScore) {
        vector<vector<int>> dp(k + 1, vector<int>(n, 0));

        // Base case: Day 0
        for (int city = 0; city < n; ++city) {
            dp[0][city] = stayScore[0][city];
        }

        // Fill the DP table
        for (int day = 1; day < k; ++day) {
            for (int currCity = 0; currCity < n; ++currCity) {
                // Option 1: Stay in the current city
                dp[day][currCity] = dp[day - 1][currCity] + stayScore[day][currCity];

                // Option 2: Move from another city
                for (int prevCity = 0; prevCity < n; ++prevCity) {
                    if (prevCity != currCity) {
                        dp[day][currCity] = max(dp[day][currCity],
                                                dp[day - 1][prevCity] + travelScore[prevCity][currCity] + stayScore[day][currCity]);
                    }
                }
            }
        }

        // Find the maximum score on the last day
        int maxPoints = 0;
        for (int city = 0; city < n; ++city) {
            maxPoints = max(maxPoints, dp[k - 1][city]);
        }

        return maxPoints;           
    }
};
