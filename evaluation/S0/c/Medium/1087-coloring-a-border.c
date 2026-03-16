// Source: https://leetcode.com/problems/coloring-a-border/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid, and three integers row, col, and color. Each value in the grid represents the color of the grid square at that location.
//
// Two squares are called adjacent if they are next to each other in any of the 4 directions.
//
// Two squares belong to the same connected component if they have the same color and they are adjacent.
//
// The border of a connected component is all the squares in the connected component that are either adjacent to (at least) a square not in the component, or on the boundary of the grid (the first or last row or column).
//
// You should color the border of the connected component that contains the square grid[row][col] with color.
//
// Return the final grid.
//
// Example:
// Input: grid = [[1,1],[1,2]], row = 0, col = 0, color = 3
// Output: [[3,3],[3,2]]
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	1 <= grid[i][j], color <= 1000
// 	0 <= row < m
// 	0 <= col < n
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** colorBorder(int** grid, int gridSize, int* gridColSize, int row, int col, int color, int* returnSize, int** returnColumnSizes) {
    int m = gridSize, n = gridColSize[0];
    int originalColor = grid[row][col];
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int visited[50][50] = {0};

    void dfs(int r, int c) {
        visited[r][c] = 1;
        int isBorder = 0;

        for (int i = 0; i < 4; i++) {
            int newRow = r + directions[i][0];
            int newCol = c + directions[i][1];

            if (newRow < 0 || newRow >= m || newCol < 0 || newCol >= n || grid[newRow][newCol] != originalColor) {
                isBorder = 1;
            } else if (!visited[newRow][newCol]) {
                dfs(newRow, newCol);
            }
        }

        if (isBorder) {
            grid[r][c] = color;
        }
    }

    dfs(row, col);

    *returnSize = m;
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        (*returnColumnSizes)[i] = n;
    }

    return grid;        
}
