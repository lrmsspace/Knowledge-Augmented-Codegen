// Source: https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n grid. Each cell of grid represents a street. The street of grid[i][j] can be:
//
//
// 	1 which means a street connecting the left cell and the right cell.
// 	2 which means a street connecting the upper cell and the lower cell.
// 	3 which means a street connecting the left cell and the lower cell.
// 	4 which means a street connecting the right cell and the lower cell.
// 	5 which means a street connecting the left cell and the upper cell.
// 	6 which means a street connecting the right cell and the upper cell.
//
//
// You will initially start at the street of the upper-left cell (0, 0). A valid path in the grid is a path that starts from the upper left cell (0, 0) and ends at the bottom-right cell (m - 1, n - 1). The path should only follow the streets.
//
// Notice that you are not allowed to change any street.
//
// Return true if there is a valid path in the grid or false otherwise.
//
// Example:
// Input: grid = [[2,4,3],[6,5,2]]
// Output: true
// Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 300
// 	1 <= grid[i][j] <= 6
//

bool hasValidPath(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    int directions[7][4] = {
        {},
        {0, -1, 0, 1},   // 1: left, right
        {-1, 0, 1, 0},   // 2: up, down
        {0, -1, 1, 0},   // 3: left, down
        {0, 1, 1, 0},    // 4: right, down
        {-1, 0, 0, -1},  // 5: up, left
        {-1, 0, 0, 1}    // 6: up, right
    };

    bool visited[m][n];
    memset(visited, false, sizeof(visited));

    typedef struct {
        int x;
        int y;
    } Point;

    Point stack[m * n];
    int top = -1;

    stack[++top] = (Point){0, 0};
    visited[0][0] = true;

    while (top >= 0) {
        Point curr = stack[top--];
        int x = curr.x;
        int y = curr.y;

        if (x == m - 1 && y == n - 1) {
            return true;
        }

        int* dir = directions[grid[x][y]];
        for (int i = 0; i < 4; i += 2) {
            int nx = x + dir[i];
            int ny = y + dir[i + 1];

            if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
                int* nextDir = directions[grid[nx][ny]];
                for (int j = 0; j < 4; j += 2) {
                    if (nx + nextDir[j] == x && ny + nextDir[j + 1] == y) {
                        visited[nx][ny] = true;
                        stack[++top] = (Point){nx, ny};
                        break;
                    }
                }
            }
        }
    }

    return false;       
}
