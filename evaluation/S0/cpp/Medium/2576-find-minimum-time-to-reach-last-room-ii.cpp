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
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size();
        int m = moveTime[0].size();
        vector<vector<long long>> dist(n, vector<long long>(m, LLONG_MAX));
        dist[0][0] = 0;

        using T = tuple<long long, int, int, int>; // time, x, y, step
        priority_queue<T, vector<T>, greater<T>> pq;
        pq.emplace(0, 0, 0, 0);

        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!pq.empty()) {
            auto [time, x, y, step] = pq.top();
            pq.pop();

            if (dist[x][y] < time) continue;

            for (const auto& [dx, dy] : directions) {
                int nx = x + dx;
                int ny = y + dy;

                if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

                long long nextTime = time + (step % 2 == 0 ? 1 : 2);
                if (nextTime < moveTime[nx][ny]) {
                    long long waitTime = moveTime[nx][ny] - nextTime;
                    if (waitTime % 2 == 1) {
                        waitTime++;
                    }
                    nextTime += waitTime;
                }

                if (nextTime < dist[nx][ny]) {
                    dist[nx][ny] = nextTime;
                    pq.emplace(nextTime, nx, ny, step + 1);
                }
            }
        }

        return dist[n - 1][m - 1];          
    }
};
