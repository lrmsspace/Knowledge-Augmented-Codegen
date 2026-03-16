// Source: https://leetcode.com/problems/longest-increasing-path-in-a-matrix/   |   Difficulty: Hard
//
// Problem Description:
// Given an m x n integers matrix, return the length of the longest increasing path in matrix.
//
// From each cell, you can either move in four directions: left, right, up, or down. You may not move diagonally or move outside the boundary (i.e., wrap-around is not allowed).
//
// Example:
// Input: matrix = [[9,9,4],[6,6,8],[2,1,1]]
// Output: 4
// Explanation: The longest increasing path is [1, 2, 6, 9].
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 200
// 	0 <= matrix[i][j] <= 231 - 1
//

int longestIncreasingPath(int** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0 || matrixColSize == NULL || matrixColSize[0] == 0) return 0;
    int rows = matrixSize;
    int cols = matrixColSize[0];
    int **dp = (int**)malloc(rows * sizeof(int*));
    if (!dp) return 0;
    for (int i = 0; i < rows; ++i) {
        dp[i] = (int*)calloc(cols, sizeof(int));
        if (!dp[i]) {
            for (int k = 0; k < i; ++k) free(dp[k]);
            free(dp);
            return 0;
        }
    }

    int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    int longest = 0;

    /* DFS with memoization */
    int dfs(int r, int c) {
        if (dp[r][c] != 0) return dp[r][c];
        int maxLen = 1;
        for (int d = 0; d < 4; ++d) {
            int nr = r + directions[d][0];
            int nc = c + directions[d][1];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && matrix[nr][nc] > matrix[r][c]) {
                int len = 1 + dfs(nr, nc);
                if (len > maxLen) maxLen = len;
            }
        }
        dp[r][c] = maxLen;
        return maxLen;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int len = dfs(i, j);
            if (len > longest) longest = len;
        }
    }

    for (int i = 0; i < rows; ++i) free(dp[i]);
    free(dp);
    return longest;     
}
