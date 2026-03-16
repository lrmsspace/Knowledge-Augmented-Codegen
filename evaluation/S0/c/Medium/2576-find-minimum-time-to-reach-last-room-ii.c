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

int minTimeToReach(int** moveTime, int moveTimeSize, int* moveTimeColSize) {
    int n = moveTimeSize;
    int m = moveTimeColSize[0];
    int dist[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dist[i][j] = 1e9;
        }
    }
    dist[0][0] = 0;

    typedef struct {
        int x, y, time;
    } Node;

    Node queue[n * m];
    int front = 0, back = 0;
    queue[back++] = (Node){0, 0, 0};

    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (front < back) {
        Node curr = queue[front++];
        for (int d = 0; d < 4; d++) {
            int nx = curr.x + directions[d][0];
            int ny = curr.y + directions[d][1];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                int nextTime = curr.time + ((curr.time % 2 == 0) ? 1 : 2);
                if (nextTime < moveTime[nx][ny]) {
                    int waitTime = moveTime[nx][ny] - nextTime;
                    if (waitTime % 2 == 1) {
                        waitTime++;
                    }
                    nextTime += waitTime;
                }
                if (nextTime < dist[nx][ny]) {
                    dist[nx][ny] = nextTime;
                    queue[back++] = (Node){nx, ny, nextTime};
                }
            }
        }
    }

    return dist[n - 1][m - 1];      
}
