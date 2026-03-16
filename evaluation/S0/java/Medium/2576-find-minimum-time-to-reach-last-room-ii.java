// Source: https://leetcode.com/problems/find-minimum-time-to-reach-last-room-ii/   |   Difficulty: Medium
//
// Problem Description:
// There is a dungeon with n x m rooms arranged as a grid.
//
// You are given a 2D array moveTime of size n x m, where moveTime[i][j] represents the minimum time in seconds when you can start moving to that room. You start from the room (0, 0) at time t = 0 and can move to an adjacent room. Moving between adjacent rooms takes one second for one move and two seconds for the next, alternating between the two.
//
// Return the minimum time to reach the room (n - 1, m - 1).
//
// Two rooms are adjacent if they share a common wall, either horizontally or vertically.
//
// Example:
// Input: moveTime = [[0,4],[4,4]]
//
// Output: 7
//
// Explanation:
//
// The minimum time required is 7 seconds.
//
//
// 	At time t == 4, move from room (0, 0) to room (1, 0) in one second.
// 	At time t == 5, move from room (1, 0) to room (1, 1) in two seconds.
//
// Constraints:
// 2 <= n == moveTime.length <= 750
// 	2 <= m == moveTime[i].length <= 750
// 	0 <= moveTime[i][j] <= 109
//

class Solution {
    public int minTimeToReach(int[][] moveTime) {
        int n = moveTime.length;
        int m = moveTime[0].length;
        int[][] time = new int[n][m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                time[i][j] = Integer.MAX_VALUE;
            }
        }
        time[0][0] = 0;

        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[2]));
        pq.offer(new int[]{0, 0, 0}); // x, y, current time

        int[][] directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int x = curr[0];
            int y = curr[1];
            int currTime = curr[2];

            if (x == n - 1 && y == m - 1) {
                return currTime;
            }

            for (int[] dir : directions) {
                int newX = x + dir[0];
                int newY = y + dir[1];

                if (newX >= 0 && newX < n && newY >= 0 && newY < m) {
                    int nextMoveTime = (currTime % 2 == 0) ? currTime + 1 : currTime + 2;
                    if (nextMoveTime < moveTime[newX][newY]) {
                        nextMoveTime = moveTime[newX][newY] + ((moveTime[newX][newY] - nextMoveTime) % 2 == 0 ? 1 : 0);
                    }

                    if (nextMoveTime < time[newX][newY]) {
                        time[newX][newY] = nextMoveTime;
                        pq.offer(new int[]{newX, newY, nextMoveTime});
                    }
                }
            }
        }

        return -1; // Should never reach here           
    }
}
