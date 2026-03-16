// Source: https://leetcode.com/problems/escape-the-spreading-fire/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array grid of size m x n which represents a field. Each cell has one of three values:
//
//
// 	0 represents grass,
// 	1 represents fire,
// 	2 represents a wall that you and fire cannot pass through.
//
//
// You are situated in the top-left cell, (0, 0), and you want to travel to the safehouse at the bottom-right cell, (m - 1, n - 1). Every minute, you may move to an adjacent grass cell. After your move, every fire cell will spread to all adjacent cells that are not walls.
//
// Return the maximum number of minutes that you can stay in your initial position before moving while still safely reaching the safehouse. If this is impossible, return -1. If you can always reach the safehouse regardless of the minutes stayed, return 109.
//
// Note that even if the fire spreads to the safehouse immediately after you have reached it, it will be counted as safely reaching the safehouse.
//
// A cell is adjacent to another cell if the former is directly north, east, south, or west of the latter (i.e., their sides are touching).
//
// Example:
// Input: grid = [[0,2,0,0,0,0,0],[0,0,0,2,2,1,0],[0,2,0,0,1,2,0],[0,0,2,2,2,0,2],[0,0,0,0,0,0,0]]
// Output: 3
// Explanation: The figure above shows the scenario where you stay in the initial position for 3 minutes.
// You will still be able to safely reach the safehouse.
// Staying for more than 3 minutes will not allow you to safely reach the safehouse.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 300
// 	4 <= m * n <= 2 * 104
// 	grid[i][j] is either 0, 1, or 2.
// 	grid[0][0] == grid[m - 1][n - 1] == 0
//

int maximumMinutes(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    
    // Function to perform BFS and calculate fire spread times
    void bfsFire(int fireTime[m][n]) {
        memset(fireTime, -1, sizeof(int) * m * n);
        int queue[m * n][2];
        int front = 0, back = 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    fireTime[i][j] = 0;
                    queue[back][0] = i;
                    queue[back][1] = j;
                    back++;
                }
            }
        }
        
        while (front < back) {
            int x = queue[front][0];
            int y = queue[front][1];
            front++;
            
            for (int d = 0; d < 4; d++) {
                int nx = x + directions[d][0];
                int ny = y + directions[d][1];
                
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] != 2 && fireTime[nx][ny] == -1) {
                    fireTime[nx][ny] = fireTime[x][y] + 1;
                    queue[back][0] = nx;
                    queue[back][1] = ny;
                    back++;
                }
            }
        }
    }
    
    // Function to check if we can reach the safehouse with a given wait time
    int canReach(int waitTime, int fireTime[m][n]) {
        int playerTime[m][n];
        memset(playerTime, -1, sizeof(int) * m * n);
        int queue[m * n][2];
        int front = 0, back = 0;
        
        playerTime[0][0] = waitTime;
        queue[back][0] = 0;
        queue[back][1] = 0;
        back++;
        
        while (front < back) {
            int x = queue[front][0];
            int y = queue[front][1];
            front++;
            for (int d = 0; d < 4; d++) {
                int nx = x + directions[d][0];
                int ny = y + directions[d][1];
                
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] != 2) {
                    int arrivalTime = playerTime[x][y] + 1;
                    if ((fireTime[nx][ny] == -1 || arrivalTime < fireTime[nx][ny]) && (playerTime[nx][ny] == -1 || arrivalTime < playerTime[nx][ny])) {
                        playerTime[nx][ny] = arrivalTime;
                        queue[back][0] = nx;
                        queue[back][1] = ny;
                        back++;
                    }
                }
            }
            if (playerTime[m-1][n-1] != -1) {
                return 1;
            }
            if (x == m - 1 && y == n - 1) {
                return 1;
            }
            
        }
        return 0;
    }
    
    int fireTime[m][n];
    bfsFire(fireTime);
    
    int left = 0, right = m * n, ans = -1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canReach(mid, fireTime)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return ans;
}