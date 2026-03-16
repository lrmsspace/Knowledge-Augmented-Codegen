// Source: https://leetcode.com/problems/swim-in-rising-water/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n integer matrix grid where each value grid[i][j] represents the elevation at that point (i, j).
//
// It starts raining, and water gradually rises over time. At time t, the water level is t, meaning any cell with elevation less than equal to t is submerged or reachable.
//
// You can swim from a square to another 4-directionally adjacent square if and only if the elevation of both squares individually are at most t. You can swim infinite distances in zero time. Of course, you must stay within the boundaries of the grid during your swim.
//
// Return the minimum time until you can reach the bottom right square (n - 1, n - 1) if you start at the top left square (0, 0).
//
// Example:
// Input: grid = [[0,2],[1,3]]
// Output: 3
// Explanation:
// At time 0, you are in grid location (0, 0).
// You cannot go anywhere else because 4-directionally adjacent neighbors have a higher elevation than t = 0.
// You cannot reach point (1, 1) until time 3.
// When the depth of water is 3, we can swim anywhere inside the grid.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 50
// 	0 <= grid[i][j] < n2
// 	Each value grid[i][j] is unique.
//

int swimInWater(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    int left = grid[0][0], right = n * n - 1;
    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

    int canReach(int t) {
        if (grid[0][0] > t) return 0;
        int visited[50][50];
        memset(visited, 0, sizeof(visited));
        visited[0][0] = 1;
        int stack[2500][2];
        int sp = 0;
        stack[sp][0] = 0; stack[sp][1] = 0; sp++;
        while (sp > 0) {
            sp--;
            int x = stack[sp][0];
            int y = stack[sp][1];
            if (x == n - 1 && y == n - 1) return 1;
            for (int d = 0; d < 4; ++d) {
                int nx = x + directions[d][0];
                int ny = y + directions[d][1];
                if (nx >= 0 && nx < n && ny >= 0 && ny < n &&
                    !visited[nx][ny] && grid[nx][ny] <= t) {
                    visited[nx][ny] = 1;
                    stack[sp][0] = nx; stack[sp][1] = ny; sp++;
                }
            }
        }
        return 0;
    }

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (canReach(mid)) right = mid;
        else left = mid + 1;
    }
    return left;        
}
