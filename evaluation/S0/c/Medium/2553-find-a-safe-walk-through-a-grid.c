// Source: https://leetcode.com/problems/find-a-safe-walk-through-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix grid and an integer health.
//
// You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1).
//
// You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive.
//
// Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1.
//
// Return true if you can reach the final cell with a health value of 1 or more, and false otherwise.
//
// Example:
// Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1
//
// Output: true
//
// Explanation:
//
// The final cell can be reached safely by walking along the gray cells below.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	2 <= m * n
// 	1 <= health <= m + n
// 	grid[i][j] is either 0 or 1.
//

bool findSafeWalk(int** grid, int gridSize, int* gridColSize, int health) {
    int m = gridSize, n = gridColSize[0];
    if (health <= 0) return false;
    if (m == 1 && n == 1) return true;

    bool visited[m][n];
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            visited[i][j] = false;

    typedef struct {
        int x, y, h;
    } Node;

    Node queue[m * n];
    int front = 0, rear = 0;

    queue[rear++] = (Node){0, 0, health - grid[0][0]};
    visited[0][0] = true;

    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

    while (front < rear) {
        Node current = queue[front++];
        for (int d = 0; d < 4; d++) {
            int newX = current.x + directions[d][0];
            int newY = current.y + directions[d][1];
            if (newX >= 0 && newX < m && newY >= 0 && newY < n) {
                int newHealth = current.h - grid[newX][newY];
                if (newHealth > 0 && !visited[newX][newY]) {
                    if (newX == m - 1 && newY == n - 1) return true;
                    visited[newX][newY] = true;
                    queue[rear++] = (Node){newX, newY, newHealth};
                }
            }
        }
    }

    return false;       
}
