// Source: https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle). You can move up, down, left, or right from and to an empty cell in one step.
//
// Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1) given that you can eliminate at most k obstacles. If it is not possible to find such walk return -1.
//
// Example:
// Input: grid = [[0,0,0],[1,1,0],[0,0,0],[0,1,1],[0,0,0]], k = 1
// Output: 6
// Explanation: 
// The shortest path without eliminating any obstacle is 10.
// The shortest path with one obstacle elimination at position (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 40
// 	1 <= k <= m * n
// 	grid[i][j] is either 0 or 1.
// 	grid[0][0] == grid[m - 1][n - 1] == 0
//

int shortestPath(int** grid, int gridSize, int* gridColSize, int k) {
    int m = gridSize, n = gridColSize[0];
    if (m == 1 && n == 1) return 0;

    typedef struct {
        int x, y, eliminations;
    } State;

    int maxStates = m * n * (k + 1);
    State *queue = (State *)malloc(maxStates * sizeof(State));
    int *visited = (int *)calloc(maxStates, sizeof(int));
    if (!queue || !visited) {
        free(queue);
        free(visited);
        return -1;
    }

    int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    int front = 0, back = 0;
    queue[back++] = (State){0, 0, 0};
    visited[0] = 1;
    int steps = 0;

    while (front < back) {
        int size = back - front;
        for (int i = 0; i < size; i++) {
            State curr = queue[front++];
            for (int d = 0; d < 4; d++) {
                int nx = curr.x + directions[d][0];
                int ny = curr.y + directions[d][1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                    int newEliminations = curr.eliminations + grid[nx][ny];
                    if (newEliminations <= k) {
                        if (nx == m - 1 && ny == n - 1) {
                            free(queue);
                            free(visited);
                            return steps + 1;
                        }
                        int stateIndex = (nx * n + ny) * (k + 1) + newEliminations;
                        if (!visited[stateIndex]) {
                            visited[stateIndex] = 1;
                            queue[back++] = (State){nx, ny, newEliminations};
                        }
                    }
                }
            }
        }
        steps++;
    }

    free(queue);
    free(visited);
    return -1;      
}
