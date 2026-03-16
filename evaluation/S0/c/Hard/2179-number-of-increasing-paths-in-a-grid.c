// Source: https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer matrix grid, where you can move from a cell to any adjacent cell in all 4 directions.
//
// Return the number of strictly increasing paths in the grid such that you can start from any cell and end at any cell. Since the answer may be very large, return it modulo 109 + 7.
//
// Two paths are considered different if they do not have exactly the same sequence of visited cells.
//
// Example:
// Input: grid = [[1,1],[3,4]]
// Output: 8
// Explanation: The strictly increasing paths are:
// - Paths with length 1: [1], [1], [3], [4].
// - Paths with length 2: [1 -> 3], [1 -> 4], [3 -> 4].
// - Paths with length 3: [1 -> 3 -> 4].
// The total number of paths is 4 + 3 + 1 = 8.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	1 <= grid[i][j] <= 105
//

int countPaths(int** grid, int gridSize, int* gridColSize) {
    int MOD = 1000000007;
    int m = gridSize, n = gridColSize[0];
    int *dp = (int*)malloc(m * n * sizeof(int));
    int **cells = (int**)malloc(m * n * sizeof(int*));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cells[i * n + j] = &grid[i][j];
            dp[i * n + j] = 1; // each cell itself is a path
        }
    }
    // Sort cells by their values
    qsort(cells, m * n, sizeof(int*), cmpInt);
    int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    for (int idx = 0; idx < m * n; idx++) {
        int val = *(cells[idx]);
        int i = (cells[idx] - &grid[0][0]) / n;
        int j = (cells[idx] - &grid[0][0]) % n;
        for (int d = 0; d < 4; d++) {
            int ni = i + directions[d][0];
            int nj = j + directions[d][1];
            if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] < val) {
                dp[i * n + j] = (dp[i * n + j] + dp[ni * n + nj]) % MOD;
            }
        }
    }
    long long result = 0;
    for (int i = 0; i < m * n; i++) {
        result = (result + dp[i]) % MOD;
    }
    free(dp);
    free(cells);
    return (int)result;     
}
