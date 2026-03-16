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
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size();
        int m = moveTime[0].size();
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        dist[0][0] = 0;

        using T = tuple<int, int, int>; // time, x, y
        priority_queue<T, vector<T>, greater<T>> pq;
        pq.emplace(0, 0, 0);

        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!pq.empty()) {
            auto [time, x, y] = pq.top();
            pq.pop();

            if (x == n - 1 && y == m - 1) {
                return time;
            }

            for (const auto& [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                    int arrivalTime = time + 1;
                    if (arrivalTime < moveTime[nx][ny]) {
                        arrivalTime = moveTime[nx][ny];
                    }

                    if (dist[nx][ny] > arrivalTime) {
                        dist[nx][ny] = arrivalTime;
                        pq.emplace(arrivalTime, nx, ny);
                    }
                }
            }
        }

        return -1; // Should never reach here           
    }
};
