// Source: https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n grid. Each cell of the grid has a sign pointing to the next cell you should visit if you are currently in this cell. The sign of grid[i][j] can be:
//
//
// 	1 which means go to the cell to the right. (i.e go from grid[i][j] to grid[i][j + 1])
// 	2 which means go to the cell to the left. (i.e go from grid[i][j] to grid[i][j - 1])
// 	3 which means go to the lower cell. (i.e go from grid[i][j] to grid[i + 1][j])
// 	4 which means go to the upper cell. (i.e go from grid[i][j] to grid[i - 1][j])
//
//
// Notice that there could be some signs on the cells of the grid that point outside the grid.
//
// You will initially start at the upper left cell (0, 0). A valid path in the grid is a path that starts from the upper left cell (0, 0) and ends at the bottom-right cell (m - 1, n - 1) following the signs on the grid. The valid path does not have to be the shortest.
//
// You can modify the sign on a cell with cost = 1. You can modify the sign on a cell one time only.
//
// Return the minimum cost to make the grid have at least one valid path.
//
// Example:
// Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
// Output: 3
// Explanation: You will start at point (0, 0).
// The path to (3, 3) is as follows. (0, 0) --> (0, 1) --> (0, 2) --> (0, 3) change the arrow to down with cost = 1 --> (1, 3) --> (1, 2) --> (1, 1) --> (1, 0) change the arrow to down with cost = 1 --> (2, 0) --> (2, 1) --> (2, 2) --> (2, 3) change the arrow to down with cost = 1 --> (3, 3)
// The total cost = 3.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 100
// 	1 <= grid[i][j] <= 4
//

int minCost(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    int dist[m][n];
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            dist[i][j] = 1e9;
    dist[0][0] = 0;

    int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };
    int deque[m*n][2];
    int front = 0, back = 0;
    deque[back][0] = 0; deque[back][1] = 0; back++;

    while (front < back) {
        int x = deque[front][0], y = deque[front][1];
        front++;
        for (int d = 0; d < 4; ++d) {
            int nx = x + dir[d][0], ny = y + dir[d][1];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            int cost = (grid[x][y] == d + 1) ? 0 : 1;
            if (dist[x][y] + cost < dist[nx][ny]) {
                dist[nx][ny] = dist[x][y] + cost;
                if (cost == 0) {
                    deque[front - 1][0] = nx;
                    deque[front - 1][1] = ny;
                } else {
                    deque[back][0] = nx;
                    deque[back][1] = ny;
                    back++;
                }
            }
        }
    }

    return dist[m - 1][n - 1];      
}
