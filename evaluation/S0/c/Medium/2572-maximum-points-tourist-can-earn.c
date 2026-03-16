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

int maxScore(int n, int k, int** stayScore, int stayScoreSize, int* stayScoreColSize, int** travelScore, int travelScoreSize, int* travelScoreColSize) {
    int dp[k][n];
    for (int city = 0; city < n; city++) {
        dp[0][city] = stayScore[0][city];
    }

    for (int day = 1; day < k; day++) {
        for (int currCity = 0; currCity < n; currCity++) {
            int maxPoints = 0;
            for (int prevCity = 0; prevCity < n; prevCity++) {
                int points = dp[day - 1][prevCity];
                if (prevCity == currCity) {
                    points += stayScore[day][currCity];
                } else {
                    points += travelScore[prevCity][currCity];
                }
                if (points > maxPoints) {
                    maxPoints = points;
                }
            }
            dp[day][currCity] = maxPoints;
        }
    }

    int result = 0;
    for (int city = 0; city < n; city++) {
        if (dp[k - 1][city] > result) {
            result = dp[k - 1][city];
        }
    }

    return result;      
}
