// Source: https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array grid of size m x n. Each cell has one of two values:
//
//
// 	0 represents an empty cell,
// 	1 represents an obstacle that may be removed.
//
//
// You can move up, down, left, or right from and to an empty cell.
//
// Return the minimum number of obstacles to remove so you can move from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1).
//
// Example:
// Input: grid = [[0,1,1],[1,1,0],[1,1,0]]
// Output: 2
// Explanation: We can remove the obstacles at (0, 1) and (0, 2) to create a path from (0, 0) to (2, 2).
// It can be shown that we need to remove at least 2 obstacles, so we return 2.
// Note that there may be other ways to remove 2 obstacles to create a path.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	2 <= m * n <= 105
// 	grid[i][j] is either 0 or 1.
// 	grid[0][0] == grid[m - 1][n - 1] == 0
//

int minimumObstacles(int** grid, int gridSize, int* gridColSize) {
    if (!grid || gridSize <= 0 || !gridColSize || gridColSize[0] <= 0) return -1;

    int m = gridSize;
    int n = gridColSize[0];
    int total = m * n;
    int *dist = (int*)malloc(total * sizeof(int));
    if (!dist) return -1;
    for (int i = 0; i < total; ++i) dist[i] = -1;

    int *queue = (int*)malloc(total * sizeof(int));
    if (!queue) { free(dist); return -1; }

    int directions[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };
    int front = 0, back = 0;
    queue[back++] = 0; /* start from (0,0) */
    dist[0] = 0;

    while (front < back) {
        int idx = queue[front++];
        int x = idx / n;
        int y = idx % n;
        for (int d = 0; d < 4; ++d) {
            int nx = x + directions[d][0];
            int ny = y + directions[d][1];
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            int nidx = nx * n + ny;
            int ndist = dist[idx] + grid[nx][ny];
            if (dist[nidx] == -1 || ndist < dist[nidx]) {
                dist[nidx] = ndist;
                if (grid[nx][ny] == 0) {
                    queue[--front] = nidx; /* push to front */
                } else {
                    queue[back++] = nidx; /* push to back */
                }
            }
        }
    }

    int result = dist[total - 1];
    free(dist);
    free(queue);
    return result;      
}
