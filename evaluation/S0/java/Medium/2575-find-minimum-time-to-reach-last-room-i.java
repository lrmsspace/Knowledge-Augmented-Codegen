// Source: https://leetcode.com/problems/find-minimum-time-to-reach-last-room-i/   |   Difficulty: Medium
//
// Problem Description:
// There is a dungeon with n x m rooms arranged as a grid.
//
// You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds after which the room opens and can be moved to. You start from the room (0, 0) at time t = 0 and can move to an adjacent room. Moving between adjacent rooms takes exactly one second.
//
// Return the minimum time to reach the room (n - 1, m - 1).
//
// Two rooms are adjacent if they share a common wall, either horizontally or vertically.
//
// Example:
// Input: moveTime = [[0,4],[4,4]]
//
// Output: 6
//
// Explanation:
//
// The minimum time required is 6 seconds.
//
//
// 	At time t == 4, move from room (0, 0) to room (1, 0) in one second.
// 	At time t == 5, move from room (1, 0) to room (1, 1) in one second.
//
// Constraints:
// 2 <= n == moveTime.length <= 50
// 	2 <= m == moveTime[i].length <= 50
// 	0 <= moveTime[i][j] <= 109
//

class Solution {
    public int minTimeToReach(int[][] moveTime) {
        int n = moveTime.length;
        int m = moveTime[0].length;
        int[][] dp = new int[n][m];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = 0;
                } else if (i == 0) {
                    dp[i][j] = Math.max(dp[i][j - 1] + 1, moveTime[i][j]);
                } else if (j == 0) {
                    dp[i][j] = Math.max(dp[i - 1][j] + 1, moveTime[i][j]);
                } else {
                    int fromTop = Math.max(dp[i - 1][j] + 1, moveTime[i][j]);
                    int fromLeft = Math.max(dp[i][j - 1] + 1, moveTime[i][j]);
                    dp[i][j] = Math.min(fromTop, fromLeft);
                }
            }
        }

        return dp[n - 1][m - 1];            
    }
}
