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
    public long maxTaxiEarnings(int n, int[][] rides) {
        Arrays.sort(rides, (a, b) -> Integer.compare(a[1], b[1]));
        long[] dp = new long[rides.length];
        dp[0] = rides[0][1] - rides[0][0] + rides[0][2];

        for (int i = 1; i < rides.length; i++) {
            long currEarning = rides[i][1] - rides[i][0] + rides[i][2];
            int l = 0, r = i - 1;
            while (l <= r) {
                int mid = l + (r - l) / 2;
                if (rides[mid][1] <= rides[i][0]) {
                    currEarning = Math.max(currEarning, dp[mid] + rides[i][1] - rides[i][0] + rides[i][2]);
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            dp[i] = Math.max(dp[i - 1], currEarning);
        }

        return dp[rides.length - 1];            
    }
}
