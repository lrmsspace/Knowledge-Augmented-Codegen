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

/**
 * @param {number} n
 * @param {number} k
 * @param {number[][]} stayScore
 * @param {number[][]} travelScore
 * @return {number}
 */
var maxScore = function(n, k, stayScore, travelScore) {
    const dp = Array.from({ length: k }, () => Array(n).fill(0));
    for (let city = 0; city < n; city++) {
        dp[0][city] = stayScore[0][city];
    }
    for (let day = 1; day < k; day++) {
        for (let currCity = 0; currCity < n; currCity++) {
            let maxPoints = 0;
            for (let prevCity = 0; prevCity < n; prevCity++) {
                const points = dp[day - 1][prevCity] + (prevCity === currCity ? stayScore[day][currCity] : travelScore[prevCity][currCity]);
                maxPoints = Math.max(maxPoints, points);
            }
            dp[day][currCity] = maxPoints;
        }
    }
    return Math.max(...dp[k - 1]);
};