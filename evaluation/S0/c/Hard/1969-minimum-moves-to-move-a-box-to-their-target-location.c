// Source: https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/   |   Difficulty: Hard
//
// Problem Description:
// A storekeeper is a game in which the player pushes boxes around in a warehouse trying to get them to target locations.
//
// The game is represented by an m x n grid of characters grid where each element is a wall, floor, or box.
//
// Your task is to move the box 'B' to the target position 'T' under the following rules:
//
//
// 	The character 'S' represents the player. The player can move up, down, left, right in grid if it is a floor (empty cell).
// 	The character '.' represents the floor which means a free cell to walk.
// 	The character '#' represents the wall which means an obstacle (impossible to walk there).
// 	There is only one box 'B' and one target cell 'T' in the grid.
// 	The box can be moved to an adjacent free cell by standing next to the box and then moving in the direction of the box. This is a push.
// 	The player cannot walk through the box.
//
//
// Return the minimum number of pushes to move the box to the target. If there is no way to reach the target, return -1.
//
// Example:
// Input: grid = [["#","#","#","#","#","#"],
//                ["#","T","#","#","#","#"],
//                ["#",".",".","B",".","#"],
//                ["#",".","#","#",".","#"],
//                ["#",".",".",".","S","#"],
//                ["#","#","#","#","#","#"]]
// Output: 3
// Explanation: We return only the number of times the box is pushed.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 20
// 	grid contains only characters '.', '#', 'S', 'T', or 'B'.
// 	There is only one character 'S', 'B', and 'T' in the grid.
//

int minPushBox(char** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    typedef struct {
        int boxR, boxC, playerR, playerC;
    } State;
    #define MAX_QUEUE (m * n * m * n)
    State queue[MAX_QUEUE];
    int dist[MAX_QUEUE];
    int front = 0, back = 0;

    State start, target;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'B') {
                start.boxR = i;
                start.boxC = j;
            } else if (grid[i][j] == 'S') {
                start.playerR = i;
                start.playerC = j;
            } else if (grid[i][j] == 'T') {
                target.boxR = i;
                target.boxC = j;
            }
        }
    }

    queue[back] = start;
    dist[back] = 0;
    back++;

    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    while (front < back) {
        State curr = queue[front];
        int curr_dist = dist[front];
        front++;

        if (curr.boxR == target.boxR && curr.boxC == target.boxC) {
            return curr_dist;
        }

        for (int d = 0; d < 4; d++) {
            int newBoxR = curr.boxR + directions[d][0];
            int newBoxC = curr.boxC + directions[d][1];
            int playerNeededR = curr.boxR - directions[d][0];
            int playerNeededC = curr.boxC - directions[d][1];

            if (newBoxR < 0 || newBoxR >= m || newBoxC < 0 || newBoxC >= n ||
                grid[newBoxR][newBoxC] == '#') continue;

            // Check if player can reach the required position to push the box
            // BFS or DFS to check reachability
            int visited[m][n];
            memset(visited, 0, sizeof(visited));
            visited[curr.boxR][curr.boxC] = 1; // Box position is blocked

            typedef struct {
                int r, c;
            } Pos;
            Pos pQueue[m * n];
            int pFront = 0, pBack = 0;
            pQueue[pBack++] = (Pos){curr.playerR, curr.playerC};
            visited[curr.playerR][curr.playerC] = 1;
            int canReach = 0;
            while (pFront < pBack) {
                Pos pCurr = pQueue[pFront++];
                if (pCurr.r == playerNeededR && pCurr.c == playerNeededC) {
                    canReach = 1;
                    break;
                }
                for (int pd = 0; pd < 4; pd++) {
                    int newPR = pCurr.r + directions[pd][0];
                    int newPC = pCurr.c + directions[pd][1];
                    if (newPR >= 0 && newPR < m && newPC >= 0 && newPC < n &&
                        grid[newPR][newPC] != '#' && !visited[newPR][newPC]) {
                        visited[newPR][newPC] = 1;
                        pQueue[pBack++] = (Pos){newPR, newPC};
                    }
                }
            }
            if (!canReach) continue;
            State next = {newBoxR, newBoxC, curr.boxR, curr.boxC};
            queue[back] = next;
            dist[back] = curr_dist + 1;
            back++;

        }
    }
    return -1;

}
