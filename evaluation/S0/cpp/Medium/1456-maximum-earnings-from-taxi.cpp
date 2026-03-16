// Source: https://leetcode.com/problems/maximum-earnings-from-taxi/   |   Difficulty: Medium
//
// Problem Description:
// There are n points on a road you are driving your taxi on. The n points on the road are labeled from 1 to n in the direction you are going, and you want to drive from point 1 to point n to make money by picking up passengers. You cannot change the direction of the taxi.
//
// The passengers are represented by a 0-indexed 2D integer array rides, where rides[i] = [starti, endi, tipi] denotes the ith passenger requesting a ride from point starti to point endi who is willing to give a tipi dollar tip.
//
// For each passenger i you pick up, you earn endi - starti + tipi dollars. You may only drive at most one passenger at a time.
//
// Given n and rides, return the maximum number of dollars you can earn by picking up the passengers optimally.
//
// Note: You may drop off a passenger and pick up a different passenger at the same point.
//
// Example:
// Input: n = 5, rides = [[2,5,4],[1,5,1]]
// Output: 7
// Explanation: We can pick up passenger 0 to earn 5 - 2 + 4 = 7 dollars.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= rides.length <= 3 * 104
// 	rides[i].length == 3
// 	1 <= starti < endi <= n
// 	1 <= tipi <= 105
//

class Solution {
public:
    long long maxTaxiEarnings(int n, vector<vector<int>>& rides) {
        // Sort rides by their end point
        sort(rides.begin(), rides.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        // DP array to store maximum earnings up to each point
        vector<long long> dp(n + 1, 0);
        int rideIndex = 0;

        for (int point = 1; point <= n; ++point) {
            // Carry forward the maximum earnings from the previous point
            dp[point] = dp[point - 1];

            // Process all rides that end at the current point
            while (rideIndex < rides.size() && rides[rideIndex][1] == point) {
                int start = rides[rideIndex][0];
                int tip = rides[rideIndex][2];
                long long earnings = (long long)(point - start) + tip;
                dp[point] = max(dp[point], dp[start] + earnings);
                ++rideIndex;
            }
        }

        return dp[n];           
    }
};
